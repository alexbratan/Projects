public class StreamC {
    private int streamType;
    private int streamGenre;
    private int streamerID;

    public int getStreamType() {
        return streamType;
    }

    public void setStreamType(int streamType) {
        this.streamType = streamType;
    }

    public int getStreamGenre() {
        return streamGenre;
    }

    public void setStreamGenre(int streamGenre) {
        this.streamGenre = streamGenre;
    }

    public int getStreamerID() {
        return streamerID;
    }

    public void setStreamerID(int streamerID) {
        this.streamerID = streamerID;
    }

    StreamC(int streamType, int streamGenre, int streamerID){
        this.streamGenre = streamGenre;
        this.streamType = streamType;
        this.streamerID = streamerID;
    }

    StreamC(){}
}
