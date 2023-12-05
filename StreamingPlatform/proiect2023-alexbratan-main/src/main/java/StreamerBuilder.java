public class StreamerBuilder {
    Streamer s = new Streamer();

    public StreamerBuilder withName(String name){
        this.s.setName(name);
        return this;
    }

    public StreamerBuilder withId(int id){
        this.s.setId(id);
        return this;
    }

    public StreamerBuilder withType(int type){
        this.s.setType(type);
        return this;
    }

    public Streamer build(){
        return s;
    }
}
