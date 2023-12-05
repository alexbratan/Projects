import java.util.*;
public class StreamFactory {
    private static final Map<Integer, StreamC> factory = new HashMap<>();

    public static StreamC getStreamC(int streamType, int streamGenre, int streamerID){
        if(factory.get(streamerID) == null) {
            StreamC c = new StreamC(streamType, streamGenre, streamerID);
            factory.put(streamerID, c);
        }
        return factory.get(streamerID);
    }
}
