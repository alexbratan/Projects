package com.example.project;

import java.io.*;
import java.util.Objects;

public class User {

    public User() {
    }

    public int searchUser(String s) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\users.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[0], s))
                    return 1;
                line = br.readLine();
            }
            br.close();
            fr.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for questions");
        }
        return 0;
    }

    public boolean checkCredentials(String username, String password) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\users.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[0], username) && Objects.equals(date[1], password))
                    return true;
                line = br.readLine();
            }
            br.close();
            fr.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for questions");
        }
        return false;
    }

    public void createUser(String username, String password) {

        try (FileWriter fw = new FileWriter("src\\main\\java\\com\\example\\project\\users.csv", true);
             BufferedWriter bw = new BufferedWriter(fw); PrintWriter pw = new PrintWriter(bw)) {
            pw.println(username + "," + password);
        } catch (IOException e) {
            System.err.println("Error writing in file for questions");

        }

    }

    public void doUserStuff(String[] arg) {

        if (arg.length < 2)
            System.out.println("{'status':'error','message':'Please provide username'}");
        else if (arg.length < 3)
            System.out.println("{'status':'error','message':'Please provide password'}");
        else if (new User().searchUser(arg[1].substring(arg[1].indexOf("'") + 1, arg[1].lastIndexOf("'"))) == 1) {
            System.out.println("{'status':'error','message':'User already exists'}");
        } else {
            System.out.println("{'status':'ok','message':'User created successfully'}");
            new User().createUser(arg[1].substring(arg[1].indexOf("'") + 1, arg[1].lastIndexOf("'")),
                    arg[2].substring(arg[2].indexOf("'") + 1, arg[2].lastIndexOf("'")));
        }

    }
}
