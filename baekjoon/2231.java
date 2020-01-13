import java.util.Scanner;
public class Main {
    public static int DIGITS(int num) {
        int count = 0;
        while(num != 0) {
            num/=10;
            count++;
        }
        return count;
    }
    public static int SUM(int num, int digits) {
        int sum = num;
        for(int i=0; i<digits; i++) {
            sum += num%10;
            num/=10;
        }
        return sum;
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        boolean flag = false;
        int digits = Main.DIGITS(N);
        
        for(int i=N-9*digits; i<N; i++) {
            if(SUM(i, digits) == N){
                System.out.println(i);
                flag = true;
                break;
            }
        }
        if(!flag)
            System.out.println("0");
    }
}