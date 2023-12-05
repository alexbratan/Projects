public class ListCmd implements Command{

    StreamDB strDB;
    public ListCmd(StreamDB strDB){
        this.strDB = strDB;
    }
    @Override
    public void execute(String s, String id, Stream str,int id1) {
        System.out.println(this.strDB.list(id1));
    }


}
