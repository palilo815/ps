public class Main {
    public static int SumOfDigits(int n) {
        int sum = 0;
        while(n > 0) {
            sum += (n%10);
            n /= 10;
        }
        return sum;
    }
    
    public static void main(String[] args) {
        int[] array = new int[10001];
        for(int i=1; i<array.length; i++) {
            if(array[i] == 0)
                System.out.println(i);
            int index = i + Main.SumOfDigits(i);
            if(index <= 10000)
                array[index]++;
        }
    }
}
