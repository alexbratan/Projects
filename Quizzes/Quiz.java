package com.example.project;

import java.io.*;
import java.util.Objects;

public class Quiz {

    public static int id = 0;
    public String user;
    public String password;
    public String[] questions = new String[]{null, null, null, null, null, null, null, null, null, null};
    public String name;
    public String is_completed = "False";
    public int q_no;

    public Quiz(String[] a) {
        this.q_no = 0;
        if (a.length > 1)
            this.user = a[1].split("'")[1];

        if (a.length > 2)
            this.password = a[2].split("'")[1];

        if (a.length > 3 && a[3].contains("-name"))
            this.name = a[3].split("'")[1];

        for (int i = 4; i < a.length; i++) {
            questions[++this.q_no] = a[i].split("'")[1];
        }
    }

    public Quiz() {

    }

    public void createQuizStuff() {
        //verific cazurile de login
        if (this.user == null || this.password == null)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(this.user, this.password)) {
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
        } else if (checkQuestions() != -1) //verific daca id-ul intrebarii exista in baza de date
            System.out.println("{ 'status' : 'error', 'message' : 'Question ID for question " + checkQuestions() + " does not exist'}");
        else if (checkQuizExists(this.name)) //verific daca exista deja un quiz cu acelasi nume in baza de date
            System.out.println("{ 'status' : 'error', 'message' : 'Quizz name already exists'}");
        else {
            id++;
            addQuiz(); //ok
            System.out.println("{ 'status' : 'ok', 'message' : 'Quizz added succesfully'}");
        }

    }

    public void getQuizStuff(String[] arg) {
        //verific cazurile de login
        if (arg.length < 3)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
        else if (!checkQuizExists(arg[3].split("'")[1])) //verific daca exista quiz-ul
            System.out.println("{ 'status' : 'error', 'message' : 'Quizz does not exist'}");
        else if (getQuizId(arg[3].split("'")[1]) != null) //ok
            System.out.println("{ 'status' : 'ok', 'message' : '" + getQuizId(arg[3].split("'")[1]) + "'}");

    }

    public void getAllQuizzes(String[] arg) {
        //verific cazurile de login
        if (arg.length < 3)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
        else
            System.out.println("{ 'status' : 'ok', 'message' : '[" + getAllQuizzes() + "]'}"); //ok

    }

    public void getQuizDetails(String[] arg) {
        //verific cazurile de login
        if (arg.length < 3)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
    }

    public void submitQuiz(String[] arg){
        //verific cazurile de login
        if (arg.length < 3)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
        else if (arg.length < 4) //verific daca s-a dat vreun identificator pentru quiz
            System.out.println("{ 'status' : 'error', 'message' : 'No quizz identifier was provided'}");
        else if (!checkQuizExistsById(arg[3].split("'")[1])) //verific daca exista quiz-ul in baza de date
            System.out.println("{ 'status' : 'error', 'message' : 'No quiz was found'}");
    }

    public void deleteQuiz(String[] arg){
        //verific cazurile de login
        if (arg.length < 3)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
        else if (arg.length < 4) //verific daca s-a dat vreun identificator pentru quiz
            System.out.println("{ 'status' : 'error', 'message' : 'No quizz identifier was provided'}");
        else if (!checkQuizExistsById(arg[3].split("'")[1])) //verific daca exista quiz-ul in baza de date
            System.out.println("{ 'status' : 'error', 'message' : 'No quiz was found'}");
        else {
            //ok
            System.out.println("{ 'status' : 'ok', 'message' : 'Quizz deleted successfully'}");
        }
    }


    public void getSolutions(String[] arg){
        //verific cazurile de login
        if (arg.length < 3)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
    }
    public void addQuiz() {
        try (FileWriter fw = new FileWriter("src\\main\\java\\com\\example\\project\\quizzes.csv", true);
             BufferedWriter bw = new BufferedWriter(fw); PrintWriter pw = new PrintWriter(bw)) {
            pw.print(id + "," + this.name + "," + this.is_completed + ",");
            for (int i = 1; i <= this.q_no; i++)
                pw.print(i + "," + this.questions[i] + ",");
            pw.println();
        } catch (IOException e) {
            System.err.println("Error writing in file for questions");

        }
    }

    public boolean checkQuizExists(String q) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\quizzes.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[1], q))
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

    public boolean checkQuizExistsById(String q) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\quizzes.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[0], q))
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
    public String getQuizId(String q) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\quizzes.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[1], q))
                    return date[0];
                line = br.readLine();
            }
            br.close();
            fr.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for questions");
        }

        return null;
    }

    public boolean checkQuestionExists(String q) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\questions.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[0], q))
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

    public int checkQuestions() {
        for (int i = 1; i <= q_no; i++)
            if (!checkQuestionExists(this.questions[i]))
                return i;
        return -1;
    }

    public void clear_id() {
        id = 0;
    }

    public String getAllQuizzes() {
        String getq = new String();
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\quizzes.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                getq += ("{\"quizz_id\" : " + "\"" + date[0] + "\"" + ", \"quizz_name\" : " + "\"" + date[1] + "\"" + ", \"is_completed\" : " + "\"" + date[2] + "\"" + "}, ");
                line = br.readLine();
            }
            br.close();
            fr.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for questions");
        }
        String fin = getq.substring(0, getq.length() - 2);
        return fin;
    }
}
