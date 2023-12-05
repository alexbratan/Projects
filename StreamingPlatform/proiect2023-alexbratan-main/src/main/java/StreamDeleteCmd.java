public class StreamDeleteCmd implements Command{

    StreamDB strDB;

    public StreamDeleteCmd(StreamDB strDB){
        this.strDB = strDB;
    }
    @Override
    public void execute(String s, String id, Stream str, int id1) {
        for(int i = 0; i < strDB.getSdb().size(); i++)
            if(strDB.getSdb().get(i).getId() == Integer.parseInt(s))
                strDB.deleteStream(Integer.parseInt(s));
    }

}
