import java.util.Objects;

public class SurpriseCmd implements Command{

    StreamDB strDB;
    UserDB usrDB;

    public SurpriseCmd(StreamDB strDB, UserDB usrDB){
        this.strDB = strDB;
        this.usrDB = usrDB;
    }

    @Override
    public void execute(String s, String id, Stream str, int id1) {
        if(Objects.equals(s, "PODCAST"))
            this.usrDB.surprise(id, this.strDB, 2);
        else if(Objects.equals(s, "SONG"))
            this.usrDB.surprise(id, this.strDB, 1);
        else
            this.usrDB.surprise(id, this.strDB, 3);
    }
}
