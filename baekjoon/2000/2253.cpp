#include <cstdio>
#include <cstring>

const int max_N = 10000;

// 140회 점프 가능
int DP[max_N + 3][142];
bool invalid[max_N + 1];
int min(int a, int b) { return a < b ? a : b; }
int main() {
    int N, M; scanf("%d %d", &N, &M);
    while (M--) {
        int x; scanf("%d", &x);
        invalid[x] = true;
    }

    memset(DP, 0x3f, sizeof(DP));
    DP[2][1] = 1;

    for (int u = 2; u < N; ++u) if (!invalid[u]) {
        DP[u + 2][2] = min(DP[u + 2][2], DP[u][1] + 1);
        DP[u + 1][1] = min(DP[u + 1][1], DP[u][1] + 1);
        for (int jump = 2; jump < 141 && u + jump <= N + 1; ++jump)
            if (DP[u][jump]) for (int k = -1; k <= 1; ++k)
                DP[u + jump + k][jump + k] = min(DP[u + jump + k][jump + k], DP[u][jump] + 1);
    }

    int ans = 1000;
    for (int i = 0; i < 141; ++i)
        ans = min(ans, DP[N][i]);
    printf("%d", ans == 1000 ? -1 : ans);
    return 0;
}