import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class UserDB {
    private ArrayList<User> udb = new ArrayList<>();

    private UserDB(){}

    private static final UserDB instance = new UserDB();

    public static UserDB getInstance(){
        return instance;
    }

    public void setAllUsersStreamsListened(ArrayList<Stream> s){
        for(int i = 0; i < this.getUdb().size(); i++)
            this.getUdb().get(i).setStreamsListened(s);
    }
    public void buildUserList (String file){
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
                finalS[2] = finalS[2].replace("\"", "");
                String s = finalS[0] + " " + finalS[1] + " " + finalS[2];
                finalS = s.split(" ");
                udb.add(new User(finalS));
            }
            fr.close();
            br.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for users");
        }

    }

    public void listen(String idu, String ids, StreamDB strDB){
        strDB.incrNoList(ids);
        for(int i = 0; i < this.getUdb().size(); i++)
            if(Integer.parseInt(idu) == this.getUdb().get(i).getId())
                this.getUdb().get(i).listen(ids);
    }

    public void recommend(String id, StreamDB strDB, int type){
        for(int i = 0; i < this.getUdb().size(); i++)
            if(this.getUdb().get(i).getId() == Integer.parseInt(id))
                System.out.println(this.getUdb().get(i).recommend(strDB, type));
    }

    public void surprise(String id, StreamDB strDB, int type){
        for(int i = 0; i < this.getUdb().size(); i++)
            if(this.getUdb().get(i).getId() == Integer.parseInt(id))
                System.out.println(this.getUdb().get(i).surprise(strDB, type));
    }
    public ArrayList<User> getUdb() {
        return udb;
    }
}
