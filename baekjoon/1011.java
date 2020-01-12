import java.util.Scanner;
public class Main {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int caseNum = scanner.nextInt();
		int[][] arr = new int[caseNum][2];
		
		for(int i=0; i<caseNum; i++) {
			arr[i][0] = scanner.nextInt();
			arr[i][1] = scanner.nextInt();
		}
		scanner.close();
		
		for(int i=0; i<caseNum; i++) {
			int n = 1;
			int count = 0;
			int distance = arr[i][1]-arr[i][0];
			
			while(distance >= n*2) {
				distance -= n * 2;
				count += 2;
				n++;
			}
			if(distance > 0)
				count++;
			if(distance > n)
				count++;
			System.out.println(count);
		}
	}
}