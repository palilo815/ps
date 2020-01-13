import java.util.Scanner;
public class Main {
    public static boolean IsItPrime(int num) {
        for(int i=2; i<=Math.sqrt(num); i++) {
            if(num % i == 0)
                return false;
        }
        if(num == 1)
            return false;
        return true;
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int[] arr = new int[N];
        for(int i=0; i<N; i++)
            arr[i] = scanner.nextInt();
        int sum = 0;
        
        for(int i=0; i<N; i++) {
            if(Main.IsItPrime(arr[i]))
                sum++;
        }
        System.out.println(sum);
    }
}