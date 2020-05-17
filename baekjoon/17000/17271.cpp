#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_M = 100;
const int mod = 1000000007;

int M;
ll A[max_M][max_M];
ll B[max_M][max_M];
ll res[max_M][max_M];

void multiply(ll x[][max_M], ll y[][max_M]) {
    memset(B, 0, sizeof(B));
    loop(i, M) loop(k, M) loop(j, M) {
        B[i][j] += x[i][k] * y[k][j];
        B[i][j] %= mod;
    }
    memcpy(x, B, sizeof(B));
}
int main() {
    ll N; cin >> N >> M;

    A[0][0] = A[0][M - 1] = 1;
    loop(i, M - 1) A[i + 1][i] = 1;
    loop(i, M) res[i][i] = 1;

    N -= M - 1;
    while (N > 0) {
        if (N & 1) multiply(res, A);
        multiply(A, A);
        N /= 2;
    }

    ll ans = 0;
    loop(i, M) ans = (ans + res[0][i]) % mod;
    cout << ans;
    return 0;
}