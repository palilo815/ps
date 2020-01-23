import java.util.Scanner;
public class Main {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        int[] R = new int[T];
        char[][] S = new char[T][];
        
        for(int i=0; i<T; i++) {
            R[i] = scanner.nextInt();
            S[i] = scanner.nextLine().toCharArray();
        }
        for(int i=0; i<T; i++) {
            for(int j=1; j<S[i].length; j++)
                for(int k=0; k<R[i]; k++)
                    System.out.print(S[i][j]);
            System.out.println("");
        }
    }
}