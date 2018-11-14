package question1014;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String string1 = scanner.nextLine();
        String string2 = scanner.nextLine();
        String string3 = scanner.nextLine();
        String string4 = scanner.nextLine();
        String[] weeks = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

        int count = 0;
        int index = 0;
        for (int i = 0; i < string1.length(); i++) {
            if(string1.charAt(i) >= 'A' && string1.charAt(i) <= 'G' && i < string2.length() && string1.charAt(i) == string2.charAt(i)){
                count++;
                if(count == 1){
                    index = i;
                    System.out.print(weeks[string1.charAt(i) - 'A'] + " ");
                    break;
                }
            }
        }

        for (int i = index + 1; i < string1.length(); i++) {
            if(i < string2.length() && string1.charAt(i) == string2.charAt(i)){
                if(string1.charAt(i) >= 'A' && string1.charAt(i) <= 'N'){
                    int hour = string1.charAt(i) - 'A' + 10;
                    System.out.print(hour + ":");
                    break;
                }else if(string1.charAt(i) >= '0' && string1.charAt(i) <= '9') {
                    System.out.print("0" + string1.charAt(i)  + ":");
                    break;
                }
            }
        }

        for (int i = 0; i < string3.length(); i++) {
            if(((string3.charAt(i) >= 'a' && string3.charAt(i) <= 'z') || (string3.charAt(i) >= 'A' && string3.charAt(i) <= 'Z'))
                    && i < string4.length() && string3.charAt(i) == string4.charAt(i)){
                if(i <= 9){
                    System.out.print("0" + i);
                }else{
                    System.out.print(i);
                }
                break;
            }
        }
    }
}
