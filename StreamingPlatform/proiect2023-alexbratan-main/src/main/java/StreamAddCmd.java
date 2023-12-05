public class StreamAddCmd implements Command{

    StreamDB strDB;

    public StreamAddCmd(StreamDB strDB){
        this.strDB = strDB;
    }

    @Override
    public void execute(String s, String id, Stream str, int id1) {
        strDB.addToSdb(str);
    }

}
