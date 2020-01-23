import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int A = scanner.nextInt();
        int B = scanner.nextInt();
        int C = scanner.nextInt();
        
        if(B >= C)
            System.out.println("-1");
        else {
            int num = A / (C - B) + 1;
            System.out.println(num);
        }
    }
}