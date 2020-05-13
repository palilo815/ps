#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 90 / 5 + 1;

bool prime[M];

double DP[M][M];
double tmp[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    double a, b; cin >> a >> b;
    a /= 100.0, b /= 100.0;

    DP[0][0] = 1.0;
    for (int t = 1; t < M; ++t) {
        memset(tmp, 0, sizeof(tmp));
        loop(A, t) loop(B, t) if (DP[A][B]) {
            tmp[A][B] += DP[A][B] * (1 - a) * (1 - b);
            tmp[A][B + 1] += DP[A][B] * (1 - a) * b;
            tmp[A + 1][B] += DP[A][B] * a * (1 - b);
            tmp[A + 1][B + 1] += DP[A][B] * a * b;
        }
        memcpy(DP, tmp, sizeof(DP));
    }

    prime[2] = prime[3] = prime[5] = prime[7] = prime[11] = prime[13] = prime[17] = true;

    double ans = 0.0;
    loop(A, M) loop(B, M)
        if (prime[A] || prime[B])
            ans += DP[A][B];
    cout << fixed << setprecision(9)
         << ans;
    return 0;
}