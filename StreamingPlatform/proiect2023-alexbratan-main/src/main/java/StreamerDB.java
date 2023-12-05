import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class StreamerDB {

    private ArrayList<Streamer> sdb = new ArrayList<>();

    private StreamerDB(){}

    private static final StreamerDB streamerDBInstance = new StreamerDB();

    public static StreamerDB getInstance(){
        return streamerDBInstance;
    }
    public void buildStreamerList (String file){
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
                sdb.add(new StreamerBuilder().withType(Integer.parseInt(finalS[0])).withName(finalS[2])
                        .withId(Integer.parseInt(finalS[1])).build());
            }
            fr.close();
            br.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for streamers");
        }

    }

    public ArrayList<Streamer> getSdb() {
        return sdb;
    }
}
