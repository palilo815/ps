import java.util.Scanner;
public class Main {
    public static boolean IsItHansu(int num) {
        if(num < 100)
            return true;
        int d1 = num % 100;
        int d2 = d1 / 10;
        d1 %= 10;	//d1 : Ã¹ ÀÚ¸´¼ö, d2 = µÎ ¹øÂ° ÀÚ¸´¼ö
        int gap = d2 - d1;
        num /= 10;
        while(num >= 10) {
            d1 = d2;
            d2 = (num % 100) / 10;
            if(gap != (d2 - d1))
                return false;
            num /= 10;
        }
        return true;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        scanner.close();
        int sum = 0;
        for(int i=1; i<=N; i++) {
            if(IsItHansu(i))
                sum++;
        }
        System.out.println(sum);
    }
}