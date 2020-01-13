import java.util.Scanner;
public class Main {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        float[] array = new float[N];
        for(int i=0; i<array.length; i++)
            array[i] = scanner.nextFloat();
        scanner.close();
        
        float max = array[0];
        for(int i=1; i<array.length; i++) {
            if(array[i] > max)
                max = array[i];
        }
        
        float sum = 0;
        for(int i=0; i<array.length; i++) {
            sum += (array[i] / max * 100);
        }
        
        System.out.println(sum/N);
    }
}