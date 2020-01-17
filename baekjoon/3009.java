import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] x = new int[3];
        int[] y = new int[3];
        for(int i=0; i<3; i++) {
            x[i] = scanner.nextInt();
            y[i] = scanner.nextInt();
        }
        scanner.close();
        
        if(x[0] == x[1])
            System.out.print(x[2]+" ");
        else if(x[1] == x[2])
            System.out.print(x[0]+" ");
        else
            System.out.print(x[1]+" ");
        if(y[0] == y[1])
            System.out.print(y[2]);
        else if(y[1] == y[2])
            System.out.print(y[0]);
        else
            System.out.print(y[1]);
    }
}