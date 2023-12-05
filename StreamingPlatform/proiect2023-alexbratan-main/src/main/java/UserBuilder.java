import java.util.ArrayList;

public class UserBuilder {
    private User usr = new User();

    public UserBuilder withId(int id){
        usr.setId(id);
        return this;
    }

    public UserBuilder withName (String name){
        usr.setName(name);
        return this;
    }

    public UserBuilder withStreams (ArrayList<Integer> streams){
        usr.setStreams(streams);
        return this;
    }

    public User build(){
        return usr;
    }
}
