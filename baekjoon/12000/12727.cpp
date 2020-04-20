#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)

const int mat[2][2] = { 6,996,1,0 };
int B[2][2];

void multiply(int tmp[][2]) {
    int res[2][2];
    loop(i, 2) loop(j, 2) {
        int x = 0;
        loop(k, 2) x += B[i][k] * tmp[k][j];
        res[i][j] = x % 1000;
    }
    memcpy(B, res, sizeof(B));
}
void power(int n) {
    if (n <= 1) return;
    int tmp[2][2];
    memcpy(tmp, B, sizeof(tmp));
    power(n / 2);
    multiply(B);
    if (n & 1) multiply(tmp);
}
int main() {
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        int N; scanf("%d", &N);
        memcpy(B, mat, sizeof(B));
        power(N);
        int ans = (B[1][0] * 6 + B[1][1] * 2) % 1000 - 1;
        printf("Case #%d: %03d\n", t, ans);
    }
    return 0;
}