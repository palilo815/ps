import java.util.Scanner;
public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int H = scanner.nextInt();
        int M = scanner.nextInt();
        
        M -= 45;
        if(M < 0) {
            H--;
            M+=60;
        }
        if(H < 0) 
            H+=24;
        System.out.println(H);
        System.out.println(M);
    }

}