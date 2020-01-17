import java.util.Scanner;
public class Main {
	public static int Rev(int num) {
		int digit100 = num/100;
		int digit1 = num%10;
		return num - digit1 - digit100 * 100 + digit100 + digit1 * 100;
	}
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int A = scanner.nextInt();
		int B = scanner.nextInt();
		
		A = Main.Rev(A);
		B = Main.Rev(B);
		
		if(A > B)
			System.out.println(A);
		else
			System.out.println(B);
	}
}