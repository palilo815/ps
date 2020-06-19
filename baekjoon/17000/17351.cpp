#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
#define max(x,y) (x>y?x:y)

const int M = 500;
const char key[] = "MOLA";

int DP[M];
char s[M + 1];

int solve(char c, int dp) {
    if (dp & 3 && c == key[dp & 3]) return ++dp;
    return ((dp >> 2) << 2) + (c == 'M');
}
int main() {
    int N; scanf("%d", &N);
    loop(i, N) {
        scanf("%s", s);
        loop(j, N) DP[j] = max(solve(s[j], DP[j]), solve(s[j], DP[j - 1]));
    }
    printf("%d", DP[N - 1] / 4);
    return 0;
}