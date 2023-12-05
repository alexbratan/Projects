import java.util.Objects;

public class RecommendCmd implements Command{

    UserDB usrDB;
    StreamDB strDB;
    public RecommendCmd(UserDB usrDB, StreamDB strDB){
        this.strDB = strDB;
        this.usrDB = usrDB;
    }

    @Override
    public void execute(String s, String id, Stream str, int id1) {
        if(Objects.equals(s, "PODCAST"))
            this.usrDB.recommend(id, this.strDB, 2);
        else if(Objects.equals(s, "SONG"))
            this.usrDB.recommend(id, this.strDB, 1);
        else
            this.usrDB.recommend(id, this.strDB, 3);
    }
}
