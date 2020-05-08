#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 2501;

int cost[max_N];
int DP[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> cost[i];

    memset(DP + 1, 0x3f, sizeof(int) * N);
    loop(i, N) {
        int c = 2 * M;
        loop(j, N - i) {
            c += cost[j];
            DP[i + j + 1] = min(DP[i + j + 1], DP[i] + c);
        }
    }
    cout << DP[N] - M;
    return 0;
}