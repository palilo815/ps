import java.util.Scanner;
public class Main {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String word = scanner.nextLine();
        scanner.close();
        
        int[] arr = new int[26];
        for(int i=0; i<word.length(); i++) {
            char c = word.charAt(i);
            if(c >= 'A' &&c <= 'Z')
                arr[c-'A']++;
            else
                arr[c-'a']++;
        }
        
        boolean duplicated = false;
        int max = 0;
        for(int i=1; i<arr.length; i++){
            if(arr[i] > arr[max]) {
                max = i;
                duplicated = false;
            }
            else if (arr[i] == arr[max])
                duplicated = true;
        }
        
        if(duplicated)
            System.out.println("?");
        else
            System.out.println((char)(max+'A'));
    }
}