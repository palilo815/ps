import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        int[] N = new int[T];
        for(int i=0; i<T; i++)
            N[i] = scanner.nextInt();

        int[][] arr = new int[41][2];
        arr[0][0] = 1;
        arr[0][1] = 0;
        arr[1][0] = 0;
        arr[1][1] = 1;
        for(int i=2; i<=40; i++) {
            arr[i][0] = arr[i-1][0] + arr[i-2][0];
            arr[i][1] = arr[i-1][1] + arr[i-2][1];
        }

        for(int i=0; i<T; i++)
            System.out.println(arr[N[i]][0] + " " + arr[N[i]][1]);
    }
}