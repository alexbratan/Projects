import java.util.ArrayList;
import java.util.List;

public class User {
    private int id;
    private String name;
    private ArrayList<Integer> streams = new ArrayList<>();
    private ArrayList<Stream> streamsListened = new ArrayList<>();
    public void setStreamsListened(ArrayList<Stream> strDB){
        for(int i = 0; i < streams.size(); i++)
            for(int j = 0; j < strDB.size(); j++)
                if(streams.get(i) == strDB.get(j).getId()) {
                    this.streamsListened.add(strDB.get(j));
                }
    }

    public ArrayList<Stream> getStreamsListened() {
        return streamsListened;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    User(){}
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Integer> getStreams() {
        return streams;
    }

    public void setStreams(ArrayList<Integer> streams) {
        this.streams = streams;
    }

    User(String[] u) {
        if (u.length >= 2) {
            this.id = Integer.parseInt(u[0]);
            this.name = u[1];
        }
           for (int i = 2; i < u.length; i++)
                this.streams.add(Integer.parseInt(u[i]));
        }

    public String recommend(StreamDB streams, int type){
        ArrayList<Stream> streamsNotListened = streams.getOtherStreamsFromStreamers(this.streamsListened);
        int j = 1;
        String listS ="[";
        for(int i = 0; i < 5 && j <= 5 && i < streamsNotListened.size();i++)
            if(streamsNotListened.get(i).getStreamCommon().getStreamType() == type)
                listS += "{" + "\"id\":" + "\"" + streamsNotListened.get(i).getId() + "\",\"" + "name\":\"" +
                        streamsNotListened.get(i).getName() + "\",\"streamerName\":\"" + streamsNotListened.get(i).getStreamerName() +
                        "\",\"noOfListenings\":\"" + streamsNotListened.get(i).getNoOfStreams() + "\",\"length\":\"" +
                        streamsNotListened.get(i).getLengthConverted() + "\",\"dateAdded\":\"" + streamsNotListened.get(i).getDateConverted() + "\"},";
        return listS.substring(0, listS.length()-1) + "]";
    }

        public String surprise(StreamDB streams, int type){
            ArrayList<Stream> surpriseStreams = streams.getStreamsSurprise(this.streamsListened);
            int j = 1;
            String listS ="[";
            for(int i = 0;j <=3 && i < surpriseStreams.size();i++)
                if(surpriseStreams.get(i).getStreamCommon().getStreamType() == type) {
                    j++;
                    listS += "{" + "\"id\":" + "\"" + surpriseStreams.get(i).getId() + "\",\"" + "name\":\"" +
                            surpriseStreams.get(i).getName() + "\",\"streamerName\":\"" + surpriseStreams.get(i).getStreamerName() +
                            "\",\"noOfListenings\":\"" + surpriseStreams.get(i).getNoOfStreams() + "\",\"length\":\"" +
                            surpriseStreams.get(i).getLengthConverted() + "\",\"dateAdded\":\"" + surpriseStreams.get(i).getDateConverted() + "\"},";
                }
            return listS.substring(0, listS.length()-1) + "]";
        }
        public void listen(String id){
            this.streams.add(Integer.parseInt(id));
        }

    }


