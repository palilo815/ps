#include<stdio.h>

int main()
{
    int N, three = 0, five = 0;
    scanf("%d", &N);
    // 남은 설탕이 5의 배수가 될 때까지 3kg봉지를 하나씩 쓴다.
    while (N > 0) {
        // 남은 설탕이 5의 배수면
        // 전부 five에 담는다.
        if (N % 5 == 0) {
            five += (N / 5);
            N = 0;
        }
        // 5의 배수가 아니면
        // three봉지 하나를 쓴다.
        else {
            N -= 3;
            ++three;
        }
    }
    
    int ans = tree + five;
    if (N != 0) ans = -1; // 3과 5로 못담는 경우, N이 음수가 된 상태로 나온다.
    printf("%d", ans);
    return 0;
}