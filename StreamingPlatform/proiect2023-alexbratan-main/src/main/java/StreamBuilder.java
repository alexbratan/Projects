public class StreamBuilder{

    private int streamType;
    private int streamGenre;
    private int streamerID;
    private int id;
    private long noOfStreams;
    private long length;
    private long dateAdded;
    private String name;
    public StreamBuilder withType(int t){
        this.streamType = t;
        return this;
    }

    public StreamBuilder withID(int id){
        this.id = id;
        return this;
    }

    public StreamBuilder withGenre(int g){
        this.streamGenre = g;
        return this;
    }

    public StreamBuilder withNoOfStreams(int n){
        this.noOfStreams = n;
        return this;
    }

    public StreamBuilder withStreamerId(int id){
        this.streamerID = id;
        return this;
    }

    public StreamBuilder withLength(long l){
        this.length = l;
        return this;
    }

    public StreamBuilder withDate(long d){
        this.dateAdded = d;
        return this;
    }

    public StreamBuilder withName(String n){
        this.name = n;
        return this;
    }

    public Stream build(){
        return new Stream(id, noOfStreams, length, dateAdded, name, streamType, streamGenre, streamerID);
    }

}
