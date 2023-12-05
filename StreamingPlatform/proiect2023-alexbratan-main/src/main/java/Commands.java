import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Commands {

    private ArrayList<String[]> cmds = new ArrayList<>();

    public void buildCommands(String file){
        try {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);

            String lineWanted = br.readLine();
            while(lineWanted!=null) {
                String[] finalS = lineWanted.split(" ");
                cmds.add(finalS);
                lineWanted = br.readLine();
            }
            fr.close();
            br.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for commands");
        }
    }

    public ArrayList<String[]> getCmds() {
        return cmds;
    }
}
