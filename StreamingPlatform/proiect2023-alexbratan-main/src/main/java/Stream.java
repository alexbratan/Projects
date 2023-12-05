import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;

public class Stream {
    private int id;
    private long noOfStreams;
    private long length;
    private long dateAdded;
    private String name;

    private String lengthConverted;

    private String dateConverted;
    private String streamerName;
    private StreamC streamCommon;

    public StreamC getStreamCommon() {
        return streamCommon;
    }

    public void setStreamCommon(StreamC streamCommon) {
        this.streamCommon = streamCommon;
    }
    Stream(){}
    Stream(int id, long noOfStreams, long length, long dateAdded, String name, int streamType, int streamGenre, int streamerID){
        this.id = id;
        this.noOfStreams = noOfStreams;
        this.length = length;
        this.dateAdded = dateAdded;
        this.name = name;
        this.streamCommon = StreamFactory.getStreamC(streamType, streamGenre, streamerID);
    }
    public String getLengthConverted(){
        long h,m,s;
        h = this.length/3600;
        m = (this.length%3600)/60;
        s = this.length % 60;
        if(h != 0)
        this.lengthConverted = String.format("%02d:%02d:%02d",h, m, s);
        else if(m != 0)
            this.lengthConverted = String.format("%02d:%02d",m, s);
        else
            this.lengthConverted = String.format("%02d", s);
        return this.lengthConverted;
    }

    public String getDateConverted(){
        Date d = new Date(this.dateAdded * 1000);
        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
        sdf.setTimeZone(TimeZone.getTimeZone("UTC"));
        this.dateConverted = sdf.format(d);
        return this.dateConverted;

    }


    public String getStreamerName() {
        return streamerName;
    }

    public void setStreamerName(String streamerName) {
        this.streamerName = streamerName;
    }


    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }


    public long getNoOfStreams() {
        return noOfStreams;
    }

    public void setNoOfStreams(long noOfStreams) {
        this.noOfStreams = noOfStreams;
    }


    public long getLength() {
        return length;
    }

    public void setLength(long length) {
        this.length = length;
    }

    public long getDateAdded() {
        return dateAdded;
    }

    public void setDateAdded(long dateAdded) {
        this.dateAdded = dateAdded;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String afisareJson(){
        String json = "{" + "\"id\":" + "\"" + id + "\",\"" +"name\":\"" + name + "\",\"streamerName\":\"" + streamerName +
                "\",\"noOfListenings\":\"" + noOfStreams + "\",\"length\":\"" + this.getLengthConverted() + "\",\"dateAdded\":\"" + this.getDateConverted() + "\"},";
        return json;
    }

}
