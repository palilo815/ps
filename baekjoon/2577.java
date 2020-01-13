import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int A, B, C;
        A = scanner.nextInt();
        B = scanner.nextInt();
        C = scanner.nextInt();
        int num = A*B*C;
        int index;
        int[] array = {0,0,0,0,0,0,0,0,0,0};
        while(num!=0) {
            index = num % 10;
            num /= 10;
            array[index]++;
        }
        for(int i=0; i<10; i++)
            System.out.println(array[i]);
    }
}