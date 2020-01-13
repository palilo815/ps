import java.util.Scanner;
public class Main {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String word = scanner.nextLine();
        
        boolean InWord = false;
        int count = 0;
        for(int i=0; i<word.length(); i++) {
            if(InWord) {
                if(word.charAt(i) == ' ')
                    InWord = false;
            }
            else {
                if(word.charAt(i) != ' ') {
                    InWord = true;
                    count++;
                }
            }
        }
        System.out.println(count);
    }
}