/* Bratan Alex-Florin 314CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
typedef struct directory {
	char *name;
	struct directory *st, *dr, *parinte, *directories;
	struct file *files;
} Dir, *TDir;
typedef struct file {
	char* name;
	struct file *st, *dr;
	struct directory *parinte;
} File, *TFile;
/* Functiile de initializare fisier sau director */
TFile addF(TDir parent, char *x) {
    TFile aux = malloc (sizeof (TFile)); //alocarea memoriei
    if (!aux)
    return NULL;
    //salvam in campul name numele directorului
    aux->name = strdup(x);
    //punem null in fiul din stanga si din dreapta
    aux->st = NULL;
    aux->dr = NULL;
    //salvam parintele in campul parinte al directorului nou
    aux->parinte = calloc (1,sizeof (TDir));
    aux->parinte = parent;
    return aux;
}
TDir addD(TDir a, char *x) {
    TDir aux = malloc (sizeof (TDir)); //alocarea memoriei
    aux->name = malloc (20);
    if (!aux)
    return NULL;
    //salvam in campul name numele fisierului
    aux->name = strdup(x);
    aux->st = NULL;
    aux->dr = NULL;
    aux->files = NULL;
    aux->directories = NULL;
     //salvam parintele in campul parinte al fisierului nou
    aux->parinte = calloc (1,sizeof (TDir));
    aux->parinte = a;
    return aux;
}
/* functiile de cautare fisier/subdirector in cadrul unui director */
int findD(TDir a, char *x) {
    while (a != NULL) {
        //daca gasim director cu numele dorit, returnam 1
        if (strcmp ( x, a->name) == 0){
            return 1;
        }
            else 
                if (strcmp ( x, a->name) < 0)
                a = a->st;
                    else 
                        a = a->dr;
    }
    //returnam 0 daca nu s-a gasit nimic
    return 0;
}
int findF(TFile a, char *x) {
    while (a != NULL) {
        //daca gasim fisier cu numele dorit, returnam 1
        if (strcmp ( x, a->name) == 0){
            return 1;
        }
            else 
                if (strcmp ( x, a->name) < 0)
                a = a->st;
                    else 
                        a = a->dr;
    }
    //returnam 0 daca nu s-a gasit nimic
    return 0;
}
/*gasirea valorii minime din cadrul unui arbore de fisiere/directoare */
TFile valMinF (TFile f){
    //ne deplasam pana la cel mai din stanga element si il returnam
    while ( f && f->st != NULL)
        f = f->st;
    return f;
}
TDir valMinD( TDir d) {
    TDir aux = d;
    //ne deplasam pana la cel mai din stanga element si il returnam
    while ( aux && aux->st != NULL)
        aux = aux->st;
    return aux;
}
/* functiile de stergere fisier/director */
TFile rm ( TFile f, char *x) {
    if ( f == NULL)
        return NULL;
    //apelam recursiv functia pana gasim fisierul cu numele dorit
    if ( strcmp ( f->name, x) > 0)
        f->st = rm ( f->st, x);
        else
            if ( strcmp ( f->name, x) < 0)
            f->dr = rm ( f->dr, x);
            else
            {   //odata ce am gasit fisierul cu numele dorit, avem 3 cazuri:
            /* CAZUL 1: daca fisierul nu are niciun fiu: 
            eliberam memoria si returnam NULL */
                if ( f->st == NULL && f->dr == NULL)
                {   
                    return NULL;
                }
                else
                /* CAZUL 2: daca fisierul are doar un fiu(st sau dr),
                 il inlocuim cu acesta */
                    if ( f->st == NULL ){
                        TFile aux = f->dr;
                        return aux;
                    }
                    else 
                        if ( f->dr == NULL) {
                            TFile aux = f->st;
                            return aux;
                        }
                        else
                        { /*CAZUL 3: daca fisierul are 2 fii:
                        cautam cel mai mic fisier dpdv lexicografic,
                        inlocuim cu acesta fisierul pe care vrem sa-l stergem
                        stergem fisierul cel mai mic lexicografic*/
                            TFile aux = valMinF (f->dr);
                            f->name = strdup(aux->name);
                            f->dr = rm (f->dr, aux->name); 
                            }
            }
    return f;        
}
TDir rmdir (TDir d, char *x) {
     if ( d == NULL)
        return d;
    //apelam recursiv functia pana gasim directorul cu numele dorit
    if ( strcmp ( d->name, x) > 0)
        d->st = rmdir ( d->st, x);
        else
            if ( strcmp ( d->name, x) < 0)
            d->dr = rmdir ( d->dr, x);
            else
            {   //odata ce am gasit directorul cu numele dorit, avem 3 cazuri:
            /* CAZUL 1: daca directorul nu are niciun fiu: 
            eliberam memoria si returnam NULL */
                if ( d->st == NULL && d->dr == NULL)
                    return NULL;
                else
                /* CAZUL 2: daca directorul are doar un fiu(st sau dr),
                 il inlocuim cu acesta */
                if ( d->st == NULL ){
                    TDir aux = d->dr;
                    return aux;
                }
                else 
                    if ( d->dr == NULL) {
                        TDir aux = d->st;
                        return aux;
                    }
                /*CAZUL 3: daca directorul are 2 fii:
                    cautam cel mai mic director dpdv lexicografic,
                    inlocuim cu acesta directorul pe care vrem sa-l stergem
                    stergem directorul cel mai mic lexicografic*/
                TDir aux = valMinD (d->dr);
                d->name = strdup(aux->name);
                d->dr = rmdir (d->dr, aux->name);
                    
            }
    return d; 
}
/*functiile de adaugare fisier/director in arborele de fisiere/subdirectoare*/
TFile touch (TFile f, char* x, TDir p)
{   //cand ajungem pe o ramura goala, initializam un fisier cu numele dorit
	if (f == NULL)
        return addF (p, x);
    if ( strcmp(f->name, x) == 0 )
        {//daca fisierul se afla in arbore, afisam mesajul si ne oprim
            printf("File %s already exists!\n", x);
            return f;
        }
        else
        //daca e mai mic lexicografic, ne deplasam in stanga
            if ( strcmp(f->name, x) > 0 )
                f->st = touch (f->st, x, p);
                else
                //daca e mai mare lexicografic, ne deplasam in dreapta
                    f->dr = touch (f->dr, x, p);
    return f;    
}
TDir mkdir (TDir d, char* x, TDir p)
{   //cand ajungem pe o ramura goala, initializam un director cu numele dorit
    if ( d == NULL)
        return addD (p , x);
    if ( strcmp (d->name, x) == 0)
        {//daca directorul se afla in arbore, afisam mesajul si ne oprim
            printf("Directory %s already exists!\n", x);
            return d;
        }
        else
        //daca e mai mic lexicografic, ne deplasam in stanga
            if ( strcmp (d->name, x) > 0)
                d->st = mkdir (d->st, x, p);
                else
                //daca e mai mare lexicografic, ne deplasam in dreapta
                    d->dr = mkdir (d->dr, x, p);   
	return d;
}
/*afisare SRD pt arbore  de directoare*/
void afiDir (TDir dir) {
    if ( dir == NULL )
        return;
    afiDir(dir->st);
    printf("%s ", dir->name);
    afiDir(dir->dr);
}
/*afisare SRD pt arbore  de fisiere*/
void afiFile (TFile file) {
    if ( file == NULL )
        return;
    afiFile(file->st);
    printf("%s ", file->name);
    afiFile(file->dr);
}
/*in ls doar apelez cele 2 functii de afisare pt fisiere/directoare */
void ls (TDir dir) {
    TDir aux = malloc(sizeof(TDir));
    aux = dir;
    afiDir(aux->directories);// SRD pt arborele de directoare
    aux = dir;
    afiFile(aux->files);//SRD pt arborele de fisiere
}
/*pwd afiseaza numele directorului a pana cand a este NULL */
void pwd(TDir a) {    
    if (a == NULL)
    return;
    pwd (a->parinte);
    printf( "/%s", a->name );
}
/*cauta directorul cu numele x si il returneaza*/
TDir cd (TDir a, char *x){
    while ( a != NULL && strcmp (a->name, x) != 0 ) {
        if ( strcmp (a->name, x) > 0)
            a = a->st;
            else 
                a = a->dr;
    }
    return a;
}

int main(){
    /* initializarea sistemului de fisiere */
    TDir sys = malloc(sizeof(TDir));
    char *a = malloc(20);
    strcpy(a, "root");
    sys = addD (sys, a);
    free(a);
    sys->parinte = NULL;
    char *command = malloc(20);
    /* initializarea vectorului de directoare */
    TDir *alldirectories = malloc(500);
    int nr = 0;
    alldirectories[nr] = sys;
    while (strcmp (command, "quit") !=0 ) {
        scanf("%s", command);
        if( strcmp (command, "touch") == 0) {
            char *f_name = malloc(20);
            scanf("%s", f_name);
            if(findD (sys->directories, f_name) == 1)
                //cautam daca exista director cu acelasi nume
                printf("Directory %s already exists!\n", f_name);
            else
                sys->files = touch(sys->files, f_name, sys);
        }
        if( strcmp (command, "mkdir") == 0) {
            char *d_name = malloc(20);
            scanf("%s", d_name);
            if(findF (sys->files, d_name) == 1)
                //cautam daca exista fisier cu acelasi nume
                printf("File %s already exists!\n", d_name);
            else
                sys->directories = mkdir(sys->directories, d_name, sys);
        }
        if ( strcmp (command, "rm") == 0) {
            char *f_name = malloc(20);
            scanf("%s", f_name);
            //daca exista fisier cu numele dorit, il stergem
            if(findF (sys->files, f_name) == 1)
                sys->files = rm(sys->files, f_name);
            else
                printf("File %s doesn't exist!\n", f_name);
                
        }
        if ( strcmp (command, "rmdir") == 0) {
            char *d_name = malloc(20);
            scanf("%s", d_name);
            if(findD(sys->directories, d_name) == 1){
                //daca exista director cu numele dorit, il stergem
                if(findF(sys->files, d_name) == 0)
                sys->directories = rmdir(sys->directories, d_name);
            }
                else
                    printf("Directory %s doesn't exist!\n", d_name);        
        }
        if( strcmp (command, "cd") == 0) {
            char *d_name = malloc(20);
            scanf("%s", d_name);
            if ( strcmp (d_name,  "..") != 0){
                if (findD (sys->directories, d_name) == 1){
                //daca exista director cu numele dorit, ne mutam in el
                    sys = cd (sys->directories, d_name);
                    //adaugam directorul in vectorul de directoare
                    nr++;
                    alldirectories[nr] = malloc(sizeof(TDir));
                    alldirectories[nr] = sys;
                }
                    else
                        printf ("Directory not found!\n");       
                }
                else {
                    //daca argumentul este ".." ne mutam in directorul parinte
                    if(sys->parinte != NULL){
                    nr++;
                    alldirectories[nr] = malloc(sizeof(TDir));
                    alldirectories[nr] = sys;
                    sys = sys->parinte;
                    }
                }
                
        }
        if ( strcmp (command, "pwd") == 0) {
            pwd(sys);
            printf("\n");
        }
        if(strcmp (command, "find") == 0) {
            char *op = malloc(3);
            scanf("%s", op);
            if(strcmp (op, "-d") == 0){
                char *d_name = malloc(20);
                scanf("%s", d_name);
            //daca optiunea este -d, parcurgem vectorul de directoare
            //daca gasim directorul cu numele dorit, afisam mesajul si calea
                int i, ok = 0;
                for( i = 0; i <= nr; i++ )
                    if(strcmp(d_name, alldirectories[i]->name) == 0){
                        printf("Directory %s found!\n", d_name);
                        pwd(alldirectories[i]);
                        printf("\n");
                        ok = 1;
                        break;
                    }
                if(ok == 0)
                    printf("Directory %s not found!\n", d_name);
            }
            else 
                {
            //daca optiunea este -d, parcurgem vectorul de directoare
            //cautam in campus files al fiecarui director
            //daca gasim fisierul, afisam mesajul si calea catre fisier
                    char *f_name = malloc(20);
                    scanf("%s", f_name);
                    int i, ok = 0;
                    for( i = 0; i <= nr; i++)
                        if(findF(alldirectories[i]->files, f_name) == 1){
                            printf("File %s found!\n", f_name);
                            pwd(alldirectories[i]);
                            printf("\n");
                            ok = 1;
                            break;
                        }
                    if(ok == 0)
                        printf("File %s not found!\n", f_name);
                }

        }
        if( strcmp (command, "ls") == 0) {
            ls(sys);
            printf("\n");
        }
    }
    return 0;
}