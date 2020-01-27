#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define scanf scanf_s
const int max_N = 2000;

bool DP[max_N][max_N];
int arr[max_N];
int main()
{
    int N; scanf("%d", &N);
    loop(i, N) scanf("%d", &arr[i]);

    // basis
    // gap이 짝수일 경우와 홀수일 경우의 basis를 둘 다 설정
    loop(i, N) DP[i][i] = true;
    loop(i, N - 1) DP[i][i + 1] = (arr[i] == arr[i + 1]);

    // 양 끝자리가 다른 경우 바로 false
    // 같다면 양 끝에서 한 칸 당김
    for (int gap = 2;gap < N;++gap)
        loop(i, N - gap) {
            if (arr[i] != arr[i + gap]) DP[i][i + gap] = false;
            else DP[i][i + gap] = DP[i + 1][i + gap - 1];
        }
    
    int M; scanf("%d", &M);
    while (M--) {
        int a, b; scanf("%d %d", &a, &b);
        printf("%d\n", DP[a - 1][b - 1]);
    }
    return 0;
}