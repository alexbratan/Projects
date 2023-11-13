#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.h"
#include "protocols.h"
#include "queue.h"
#include <arpa/inet.h>
struct route_table_entry *rtable;
int rtable_len;


struct arp_entry *arp_table;
int arp_table_len;


void print_ip_address(uint32_t ip_addr) {
    uint8_t *ip_bytes = (uint8_t *) &ip_addr;
    printf("%d.%d.%d.%d\n", ip_bytes[0], ip_bytes[1], ip_bytes[2], ip_bytes[3]);
}

struct route_table_entry *get_best_route(uint32_t ip_dest) {
	
	struct route_table_entry *best = NULL;
	for (int i = 0; i < rtable_len; i++) {
		if ((ip_dest & rtable[i].mask) == rtable[i].prefix) {

			if (best == NULL)
				best = &rtable[i];
			else if (ntohl(best->mask) < ntohl(rtable[i].mask)) {

				print_ip_address(rtable[i].prefix);
				print_ip_address(rtable[i].mask);
				printf("#### %d\n", rtable[i].interface);
				best = &rtable[i];
			}
		}
	}
	
	return best;
}

struct arp_entry *get_arp_entry(uint32_t ip_dest) {

	for (int i = 0; i < arp_table_len; i++)
	{
		if (arp_table[i].ip == ip_dest)
		{
			return &arp_table[i];
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	char buf[MAX_PACKET_LEN];
	
	// Do not modify this line
	init(argc - 2, argv + 2);

	rtable = malloc(sizeof(struct route_table_entry) * 66000);
	DIE(rtable == NULL, "memory");
	
	arp_table = malloc(sizeof(struct arp_entry) * 66000);
	/* Read the static routing table and the arp table */
	rtable_len = read_rtable(argv[1], rtable);
	arp_table_len = parse_arp_table("arp_table.txt", arp_table);
	while (1) {
		
		size_t len;
		int interface;

		struct ether_header *eth_hdr = (struct ether_header *) buf;
		struct iphdr *ip_hdr = (struct iphdr *)(buf + sizeof(struct ether_header));

		interface = recv_from_any_link(buf, &len);
		DIE(interface < 0, "get_message");
		
		uint16_t old_check = ip_hdr->check;
		ip_hdr->check = 0;
		if(old_check != htons(checksum((uint16_t *)ip_hdr, sizeof(struct iphdr))))
		{
			printf("Packet cu CKECK gresit %x %x!\n", old_check, htons(checksum((uint16_t *)ip_hdr, sizeof(struct iphdr))));
			memset(buf, 0, sizeof(buf));
			continue;
		}

		
		struct route_table_entry *best_router = get_best_route(ip_hdr->daddr);
		if(best_router == NULL)
			continue;
		

		
		if(ip_hdr->ttl <= 1)
			continue;
		
		uint16_t old_ttl;
		old_ttl = ip_hdr->ttl;
		ip_hdr->ttl--;

		ip_hdr->check = ~(~old_check +  ~((uint16_t)old_ttl) + (uint16_t)ip_hdr->ttl) - 1;

		struct arp_entry *nexthop_arp= get_arp_entry(best_router->next_hop);
		if (nexthop_arp == NULL)
			continue;
	

		memcpy(eth_hdr->ether_dhost, nexthop_arp->mac, sizeof(eth_hdr->ether_dhost));
		get_interface_mac(best_router->interface, eth_hdr->ether_shost);
		send_to_link(best_router->interface, buf, len);
	}
}


