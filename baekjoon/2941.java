import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String S = scanner.nextLine();
        int count = 1;
        for(int i=1; i<S.length(); i++) {
            if(S.charAt(i)=='=' && (S.charAt(i-1)=='c' || S.charAt(i-1)=='s'))
                continue;
            if(S.charAt(i)=='-' && (S.charAt(i-1)=='c' || S.charAt(i-1)=='d'))
                continue;
            if(S.charAt(i)=='j' && (S.charAt(i-1)=='l' || S.charAt(i-1)=='n'))
                continue;
            if(i>1 && S.charAt(i)=='=' && S.charAt(i-1)=='z' && S.charAt(i-2)=='d') {
                count--;
                continue;
            }
            if(S.charAt(i)=='=' && S.charAt(i-1)=='z')
                continue;
            count++;
        }
        System.out.println(count);
    }
}