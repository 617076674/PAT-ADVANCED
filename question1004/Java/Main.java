package question1004;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int count = scanner.nextInt();
        scanner.nextLine();
        ArrayList<Student> arrayList = new ArrayList<>();
        for (int i = 0; i < count; i++) {
            String[] messages = scanner.nextLine().split(" ");
            arrayList.add(new Student(messages[0], messages[1], Integer.parseInt(messages[2])));
        }
        Student maxScoreStudent = arrayList.get(0);
        Student minScoreStudent = arrayList.get(0);
        for (int i = 1; i < count; i++) {
            if(maxScoreStudent.score < arrayList.get(i).score){
                maxScoreStudent = arrayList.get(i);
            }
            if(minScoreStudent.score > arrayList.get(i).score){
                minScoreStudent = arrayList.get(i);
            }
        }
        System.out.println(maxScoreStudent.name + " " + maxScoreStudent.number);
        System.out.println(minScoreStudent.name + " " + minScoreStudent.number);
    }
}

class Student{
    public String name;
    public String number;
    public Integer score;

    public Student(String name, String number, Integer score){
        this.name = name;
        this.number = number;
        this.score = score;
    }
}
