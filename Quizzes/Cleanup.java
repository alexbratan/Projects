package com.example.project;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Objects;

public class Cleanup {

    public void cleanup() throws IOException {
        BufferedWriter uwriter = Files.newBufferedWriter(Paths.get("src\\main\\java\\com\\example\\project\\users.csv"));
        uwriter.write("");
        BufferedWriter qwriter = Files.newBufferedWriter(Paths.get("src\\main\\java\\com\\example\\project\\questions.csv"));
        qwriter.write("");
        BufferedWriter quizwriter = Files.newBufferedWriter(Paths.get("src\\main\\java\\com\\example\\project\\quizzes.csv"));
        quizwriter.write("");
    }
}
