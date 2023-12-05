import java.time.LocalDateTime;
import java.util.Objects;

public class ProiectPOO {

    public static void main(String[] args) {
        if (args == null) {
            System.out.println("Nothing to read here");
        } else {
            //initializez bazele de date si comenzile
            StreamDB strDB = StreamDB.getInstance();
            strDB.buildStreamList("src/main/resources/" + args[1]);
            UserDB usrDB = UserDB.getInstance();
            usrDB.buildUserList("src/main/resources/" + args[2]);
            usrDB.setAllUsersStreamsListened(strDB.getSdb());
            StreamerDB sDB = StreamerDB.getInstance();
            sDB.buildStreamerList("src/main/resources/" + args[0]);
            strDB.setStreamerNames(sDB);
            Commands commands = new Commands();
            commands.buildCommands("src/main/resources/" + args[3]);
            //parcurg comenzile si le execut
            for (int i = 0; i < commands.getCmds().size(); i++) {
                String cmd = commands.getCmds().get(i)[1];
                String cmdId = commands.getCmds().get(i)[0];
                //LIST
                if (Objects.equals(cmd, "LIST")) {
                    int ok = 0;
                    for (int j = 0; j < usrDB.getUdb().size(); j++) {
                        if (Integer.parseInt(cmdId) == usrDB.getUdb().get(j).getId()) {
                            String s = "[";
                            ok = 1;
                            for (int k = 0; k < usrDB.getUdb().get(j).getStreams().size(); k++)
                                for (int l = 0; l < strDB.getSdb().size(); l++)
                                    if (usrDB.getUdb().get(j).getStreams().get(k) == strDB.getSdb().get(l).getId())
                                        s += strDB.getSdb().get(l).afisareJson();
                            s =s.substring(0, s.length()-1);
                            s += "]";
                            System.out.println(s);
                        }
                    }
                    if(ok == 0)
                    new ListCmd(strDB).execute(new String(),new String(),new Stream(),Integer.parseInt(cmdId));
                    }
                //ADD
                if (Objects.equals(cmd, "ADD")){
                    String nameS = "";
                    for(int j = 6; j < commands.getCmds().get(i).length; j++)
                        nameS+=commands.getCmds().get(i)[j] + " ";
                    nameS = nameS.substring(0, nameS.length() - 1);
                    LocalDateTime now = LocalDateTime.now();
                    Stream s = new StreamBuilder().withType(Integer.parseInt(commands.getCmds().get(i)[2]))
                            .withStreamerId(Integer.parseInt(cmdId)).withID(Integer.parseInt(commands.getCmds().get(i)[3]))
                            .withGenre(Integer.parseInt(commands.getCmds().get(i)[4])).withLength(Long.parseLong(commands.getCmds().get(i)[5]))
                            .withName(nameS).withNoOfStreams(0).withDate(now.getSecond()).build();
                    new StreamAddCmd(strDB).execute(new String(),new String(),s, 0);
                    for (int j = 0; j < sDB.getSdb().size(); j++)
                        if (sDB.getSdb().get(j).getId() == strDB.getSdb().get(strDB.getSdb().size()-1).getStreamCommon().getStreamerID())
                            strDB.getSdb().get(strDB.getSdb().size()-1).setStreamerName(sDB.getSdb().get(j).getName());
                }
                //DELETE
                if (Objects.equals(cmd, "DELETE")){
                    new StreamDeleteCmd(strDB).execute(commands.getCmds().get(i)[2], new String(), new Stream(), 0);
                }
                //LISTEN
                if (Objects.equals(cmd, "LISTEN")){
                    new ListenCmd(strDB,usrDB).execute(commands.getCmds().get(i)[2], cmdId, new Stream(),0);
                }
                //RECOMMEND
                if(Objects.equals(cmd, "RECOMMEND")){
                    new RecommendCmd(usrDB, strDB).execute(commands.getCmds().get(i)[2], cmdId, new Stream(), 0);
                }
                //SURPRISE
                if(Objects.equals(cmd, "SURPRISE")){
                    new SurpriseCmd(strDB, usrDB).execute(commands.getCmds().get(i)[2], cmdId, new Stream(), 0);
                }
                }
            //dupa executarea tuturor comenzilor, fac curat in bazele de date
            clear(strDB, usrDB, sDB, commands);
            }
        }
        public static void clear(StreamDB strDB, UserDB usrDB, StreamerDB sDB, Commands commands){
            strDB.getSdb().clear();
            usrDB.getUdb().clear();
            sDB.getSdb().clear();
            commands.getCmds().clear();
        }
    }
