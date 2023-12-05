public class ListenCmd implements Command{
    StreamDB strDB;
    UserDB usrDB;

    public ListenCmd(StreamDB strDB, UserDB usrDB){
        this.strDB = strDB;
        this.usrDB = usrDB;
    }
    @Override
    public void execute(String s, String id, Stream str, int id1) {
        usrDB.listen(id,s,this.strDB);
        usrDB.setAllUsersStreamsListened(strDB.getSdb());
    }
}
