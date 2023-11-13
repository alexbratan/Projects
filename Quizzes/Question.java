package com.example.project;

import java.io.*;
import java.util.Objects;

public class Question {

    public Question() {

    }

    static int answer_id = 0;
    static int id = 0;
    public int index;
    public int a_no; //nr. de raspunsuri
    public int i_c_no;
    public String text; //textul intrebarii
    public String user;
    public String password;
    public String[] answers = new String[]{null, null, null, null, null, null}; //vector in care stochez raspunsurile
    public int[] is_correct = new int[]{-1, -1, -1, -1, -1, -1}; //vector in care stochez daca fiecare raspuns e corect sau nu
    public String type; //tipul variabilei

    public Question(String[] a) {
        this.a_no = 0;
        this.i_c_no = 0;
        this.index = a.length;
        if (a.length > 1)
            this.user = a[1].split("'")[1];

        if (a.length > 2)
            this.password = a[2].split("'")[1];

        if (a.length > 3 && a[3].contains("-text"))
            this.text = a[3].split("'")[1];

        if (a.length > 4 && a[4].contains("-type"))
            this.type = a[4].split("'")[1];

        for (int i = 5; i < a.length; i++) {
            if (a[i].contains("-is-correct")) {
                answer_id++;
                ++this.a_no;
                if (a[i - 1].contains("answer") && !a[i - 1].contains("-is-correct"))
                    this.answers[a_no] = a[i - 1].split("'")[1];
            }
        }


        for (int i = 5; i < a.length - 1; i++) {
            if (!a[i].contains("-is-correct")) {
                ++this.i_c_no;
                if (Objects.equals(a[i + 1].split("'")[1], "1") && a[i + 1].contains("-is-correct"))
                    is_correct[this.i_c_no] = 1;
                else if (Objects.equals(a[i + 1].split("'")[1], "0") && a[i + 1].contains("-is-correct"))
                    is_correct[this.i_c_no] = 0;
            }
        }

    }

    public void createQuestionStuff() {
        //verific cazurile de login
        if (this.user == null || this.password == null)
            System.out.println("{'status':'error','message':'You need to be authenticated'}");
        else if (!new User().checkCredentials(this.user, this.password))
            System.out.println("{'status':'error','message':'Login failed'}");
        else if (this.text == null) //verific daca am text
            System.out.println("{ 'status' : 'error', 'message' : 'No question text provided'}");
        else if (this.a_no == 0) //verific daca am raspunsuri
            System.out.println("{ 'status' : 'error', 'message' : 'No answer provided'}");
        else if (this.index == 7) //verific daca am doar un singur raspuns
            System.out.println("{ 'status' : 'error', 'message' : 'Only one answer provided'}");
        else if (checkDuplicateAnswers()) //verific daca am raspunsuri duplicate
            System.out.println("{ 'status' : 'error', 'message' : 'Same answer provided more than once'}");
        else if (checkAnswerHasNoDesc() != -1) //verific daca raspunsul nu are descriere
            System.out.println("{ 'status' : 'error', 'message' : 'Answer " + checkAnswerHasNoDesc() + " has no answer description'}");
        else if (checkNoAnswerFlag() != -1) //verific daca raspunsul nu are valoare de corectitudine
            System.out.println("{ 'status' : 'error', 'message' : 'Answer " + checkNoAnswerFlag() + " has no answer correct flag'}");
        else if (Objects.equals(this.type, "single") && correctAnswersNumber() > 1) //verific daca o intrebare single are mai multe raspunsuri corecte
            System.out.println("{ 'status' : 'error', 'message' : 'Single correct answer question has more than one correct answer'}");
        else if (checkQuestionAlreadyExists(this.text)) //verific daca intrebarea exista deja
            System.out.println("{ 'status' : 'error', 'message' : 'Question already exists'}");
        else {
            addQuestion(); //adaug intrebarea
            System.out.println("{ 'status' : 'ok', 'message' : 'Question added successfully'}");
        }

    }

    public void getQuestionStuff(String[] arg) {
        //verific cazurile de login
        if (arg.length < 3)
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
        else if (arg.length > 3 && !checkQuestionAlreadyExists(arg[3].split("'")[1])) //verific daca intrebarea nu exista
            System.out.println("{ 'status' : 'error', 'message' : 'Question does not exist'}");
        else
            System.out.println("{ 'status' : 'ok', 'message' : '" + getQuestionId(arg[3].split("'")[1]) + "'"); //OK
    }

    public void getAllQuestions(String[] arg) {
        if (arg.length < 3) //verific cazuile de login
            System.out.println("{ 'status' : 'error', 'message' : 'You need to be authenticated'}");
        else if (!new User().checkCredentials(arg[1].split("'")[1], arg[2].split("'")[1]))
            System.out.println("{ 'status' : 'error', 'message' : 'Login failed'}");
        else { //OK
            System.out.print("{'status':'ok', 'message':'[");
            System.out.print(getAllQuestions(arg[1].split("'")[1]));
            System.out.print("]'}");
        }
    }

    public boolean checkDuplicateAnswers() {
        for (int i = 1; i < this.a_no; i++)
            for (int j = i + 1; j <= this.a_no; j++)
                if (Objects.equals(this.answers[i], this.answers[j]))
                    return true;
        return false;
    }

    public int checkAnswerHasNoDesc() {
        for (int i = 1; i <= this.a_no; i++) {
            if (this.answers[i] == null && this.answers[i + 1] != null)
                return i;
        }
        return -1;
    }

    public int checkNoAnswerFlag() {
        for (int i = 1; i <= this.i_c_no; i++) {
            if (this.is_correct[i] == -1 && this.is_correct[i + 1] != -1)
                return i;
        }
        return -1;
    }

    public int correctAnswersNumber() {
        int nr = 0;
        for (int i = 1; i <= this.i_c_no; i++)
            if (this.is_correct[i] == 1)
                nr++;
        return nr;
    }

    public boolean checkQuestionAlreadyExists(String q) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\questions.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[2], q))
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

    public String getQuestionId(String q) {
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\questions.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[2], q))
                    return date[1];
                line = br.readLine();
            }
            br.close();
            fr.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for questions");
        }
        return null;
    }

    public String getAllQuestions(String u) {
        String getq = new String();
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\questions.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[1], u))
                    getq += ("{\"question_id\" : " + "\"" + date[0] + "\"" + ", \"question_name\" : " + "\"" + date[2] + "\"" + "}, ");
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

    public void addQuestion() {
        id++;
        try (FileWriter fw = new FileWriter("src\\main\\java\\com\\example\\project\\questions.csv", true);
             BufferedWriter bw = new BufferedWriter(fw); PrintWriter pw = new PrintWriter(bw)) {

            pw.print(id + "," + this.user + "," + this.text + "," + this.type +",");
            for (int i = 1; i <= this.a_no; i++)
                pw.print(this.answers[i] + "," + this.is_correct[i] + ",");
            pw.println();
        } catch (IOException e) {
            System.err.println("Error writing in file for questions");

        }
    }

    public String getQuestionDetailsById(String id){
        try {
            FileReader fr = new FileReader("src\\main\\java\\com\\example\\project\\questions.csv");
            BufferedReader br = new BufferedReader(fr);
            String line = br.readLine();
            while (line != null) {
                String[] date = line.split(",", 0);
                if (Objects.equals(date[0], id)) {
                    String q = "'[{\"question-name\":" + "\"" +date[2] + "\"" +", \"question_index\":" + "\"" + date[0]
                            + "\"" + ", \"question_type\":" + "\"" +date[3] + "\"";
                }
                line = br.readLine();
            }
            br.close();
            fr.close();

        } catch (IOException e) {
            System.err.println("Error found at reading file for questions");
        }
        return null;
    }
    public void clear_id() {
        id = 0;
        answer_id = 0;
    }
}
