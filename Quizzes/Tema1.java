package com.example.project;

import java.io.*;
import java.util.Objects;


public class Tema1 {


    public static void main(final String[] args) {


        if (args == null || args.length == 0) {
            System.out.print("Hello world!");
        } else {


            if (Objects.equals(args[0], "-create-user"))
                new User().doUserStuff(args);
            else if (Objects.equals(args[0], "-cleanup-all")) {
                new Question().clear_id();
                new Quiz().clear_id();
                try {
                    new Cleanup().cleanup();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            } else if (Objects.equals(args[0], "-create-question")) {
                Question question = new Question(args);
                question.createQuestionStuff();
            } else if (Objects.equals(args[0], "-get-question-id-by-text")) {
                new Question().getQuestionStuff(args);
            } else if (Objects.equals(args[0], "-get-all-questions")) {
                new Question().getAllQuestions(args);
            } else if (Objects.equals(args[0], "-create-quizz")) {
                Quiz q = new Quiz(args);
                q.createQuizStuff();
            } else if (Objects.equals(args[0], "-get-quizz-by-name")) {
                new Quiz().getQuizStuff(args);
            } else if (Objects.equals(args[0], "-get-all-quizzes")) {
                new Quiz().getAllQuizzes(args);
            } else if (Objects.equals(args[0], "-get-quizz-details-by-id")) {
                new Quiz().getQuizDetails(args);
            } else if (Objects.equals(args[0], "-submit-quizz")) {
                new Quiz().submitQuiz(args);
            } else if (Objects.equals(args[0], "-delete-quizz-by-id")) {
                new Quiz().deleteQuiz(args);
            } else if (Objects.equals(args[0], "-get-my-solutions")){
                new Quiz().getSolutions(args);
            }

        }
    }
}




