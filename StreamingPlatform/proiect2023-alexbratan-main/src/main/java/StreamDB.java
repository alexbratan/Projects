import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

public class StreamDB {

    private ArrayList<Stream> sdb = new ArrayList<>();

    private StreamDB(){
    }

    private static final StreamDB strInstance = new StreamDB();

    public static StreamDB getInstance(){
        return strInstance;
    }

    public void setStreamerNames(StreamerDB sDB){
        for (int i = 0; i < this.getSdb().size(); i++) {
            for (int j = 0; j < sDB.getSdb().size(); j++)
                if (sDB.getSdb().get(j).getId() == this.getSdb().get(i).getStreamCommon().getStreamerID())
                    this.getSdb().get(i).setStreamerName(sDB.getSdb().get(j).getName());
        }
    }

    public ArrayList<Stream> getOtherStreamsFromStreamers(ArrayList<Stream> streams) {
        ArrayList<Stream> newStreams = this.getSdb();
        for (int i = 0; i < streams.size(); i++)
            for (int j = 0; j < newStreams.size(); j++) {
                if (streams.get(i).getId() == newStreams.get(j).getId() ||
                        streams.get(i).getStreamCommon().getStreamerID() != newStreams.get(i).getStreamCommon().getStreamerID())
                    newStreams.remove(j);
            }
        return this.sortNoOfStreams(newStreams);
    }

    public ArrayList<Stream> sortNoOfStreams(ArrayList<Stream> streams){
            for(int i = 0; i < streams.size() - 1; i++)
                for(int j = i; j < streams.size(); j++)
                    if(streams.get(i).getNoOfStreams() < streams.get(j).getNoOfStreams()) {
                        Stream aux = streams.get(i);
                        streams.set(i, streams.get(j));
                        streams.set(j, aux);
                    }
            return streams;
        }
    public ArrayList<Stream> sortSurprise(ArrayList<Stream> streams){
        for(int i = 0; i < streams.size() - 1; i++)
            for(int j = i + 1; j < streams.size(); j++)
                if(streams.get(i).getDateAdded() < streams.get(j).getDateAdded()) {
                    Stream aux = streams.get(i);
                    streams.set(i, streams.get(j));
                    streams.set(j, aux);
                } else if(streams.get(i).getDateAdded() == streams.get(j).getDateAdded()){
                    Stream aux = streams.get(i);
                    streams.set(i, streams.get(j));
                    streams.set(j, aux);
                }
        return streams;
    }

    public ArrayList<Stream> getStreamsSurprise(ArrayList<Stream> streams){
        ArrayList<Stream> newStreams = this.getSdb();
        for(int i = 0; i < streams.size(); i++)
            for(int j = 0; j < newStreams.size(); j++){
                if(streams.get(i).getStreamCommon().getStreamerID() == newStreams.get(j).getStreamCommon().getStreamerID()){
                    newStreams.remove(j);
                }
            }
        return this.sortSurprise(newStreams);
    }

    public void buildStreamList (String file){
        try {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);

               String lineWanted = br.readLine();
            while(lineWanted!=null) {
                lineWanted = br.readLine();
                if (lineWanted == null)
                    break;
                String[] finalS = lineWanted.split("\",\"");
                finalS[0] = finalS[0].replace("\"", "");
                finalS[finalS.length-1] = finalS[finalS.length-1].replace("\"", "");
                sdb.add(new StreamBuilder().withType(Integer.parseInt(finalS[0])).withID(Integer.parseInt(finalS[1]))
                        .withGenre(Integer.parseInt(finalS[2]))
                        .withNoOfStreams(Integer.parseInt(finalS[3])).withStreamerId(Integer.parseInt(finalS[4]))
                        .withLength(Long.parseLong(finalS[5])).withDate(Long.parseLong(finalS[6]))
                        .withName(finalS[7]).build());
            }
            fr.close();
            br.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for streams");
        }

    }

    public String list(int id){
        String listS ="[";
        for(int i = 0; i < sdb.size();i++)
            if(sdb.get(i).getStreamCommon().getStreamerID() == id) {
                listS += "{" + "\"id\":" + "\"" + sdb.get(i).getId() + "\",\"" + "name\":\"" + sdb.get(i).getName() + "\",\"streamerName\":\"" + sdb.get(i).getStreamerName() +
                        "\",\"noOfListenings\":\"" + sdb.get(i).getNoOfStreams() + "\",\"length\":\"" + sdb.get(i).getLengthConverted() + "\",\"dateAdded\":\"" + sdb.get(i).getDateConverted() + "\"},";

            }
            return listS.substring(0, listS.length()-1) + "]";
    }
    public ArrayList<Stream> getSdb() {
        return sdb;
    }

    public void addToSdb(Stream s){
        sdb.add(s);
    }

    public void deleteStream(int id){
        for(int i = 0; i < this.sdb.size(); i++)
            if(this.sdb.get(i).getId() == id) {
                this.sdb.remove(i);

            }
    }


    public void incrNoList(String id){
        for(int i = 0; i < this.getSdb().size(); i++)
            if(this.getSdb().get(i).getId() == Integer.parseInt(id))
                this.getSdb().get(i).setNoOfStreams(this.getSdb().get(i).getNoOfStreams() + 1);
    }
}
