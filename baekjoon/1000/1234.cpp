#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cache[11][101][101][101];

ll fac(int n) {
    ll ret = 1;
    for (int i = 2; i <= n; ++i)
        ret *= i;
    return ret;
}
ll DP(int N, int R, int G, int B) {
    if (N == 0) return 1;
    ll& ret = cache[N][R][G][B];
    if (ret != -1) return ret;

    ret = 0;
    if (N <= R) ret += DP(N - 1, R - N, G, B);
    if (N <= G) ret += DP(N - 1, R, G - N, B);
    if (N <= B) ret += DP(N - 1, R, G, B - N);
    if (N % 2 == 0) {
        int use = N / 2;
        ll cnt = fac(N) / fac(use) / fac(use);
        if (use <= R && use <= G)
            ret += cnt * DP(N - 1, R - use, G - use, B);
        if (use <= G && use <= B)
            ret += cnt * DP(N - 1, R, G - use, B - use);
        if (use <= B && use <= R)
            ret += cnt * DP(N - 1, R - use, G, B - use);
    }
    if (N % 3 == 0) {
        int use = N / 3;
        ll cnt = fac(N) / fac(use) / fac(use) / fac(use);
        if (use <= R && use <= G && use <= B)
            ret += cnt * DP(N - 1, R - use, G - use, B - use);
    }
    return ret;
}
int main() {
    memset(cache, -1, sizeof(cache));
    int N, R, G, B;
    cin >> N >> R >> G >> B;
    cout << DP(N, R, G, B);
    return 0;
}