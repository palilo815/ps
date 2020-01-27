import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String word = scanner.nextLine();
        scanner.close();
        int sum = 0;
        for (int i = 0; i < word.length(); i++) {
            if (word.charAt(i) < 'S')
                sum += (word.charAt(i) - 'A') / 3 + 3;
            else if (word.charAt(i) == 'S')
                sum += 8;
            else if (word.charAt(i) < 'W')
                sum += 9;
            else
                sum += 10;
        }
        System.out.println(sum);
    }
}