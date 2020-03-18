#include <iostream>
#include <string.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;
const int mod = 10007;

int DP[2][max_N][max_N];

int main() {
    int N; cin >> N;
    DP[1][0][1] = DP[1][1][0] = 1;
    
    for (int i = 1; i < N - 1; ++i) {
        int src = i % 2, dst = 1 - (i % 2);
        memset(DP[dst], 0, sizeof(DP[dst]));
        loop(a, i + 1) loop(b, i + 1) if (a != b && DP[src][a][b]) {
            int& x = DP[src][a][b];
            x %= mod;
            DP[dst][a][b] += x;
            DP[dst][a + 1][b] += x;
            DP[dst][a][b + 1] += x;
            DP[dst][a + 1][b + 1] += x;
        }
    }

    int dst = 1 - N % 2, ans = 0;
    loop(a, N) loop(b, N) if (a != b)
        ans += DP[dst][a][b];
    cout << ans % mod;
    return 0;
}