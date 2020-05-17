#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_M = 100;
const int mod = 1000000007;

int N, M;
ll A[max_M][max_M];
ll B[max_M][max_M]; // temporal matrix
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
    // M = size of matrix
    cin >> N >> M;

    // initialize res to I
    loop(i, M) res[i][i] = 1;

    // A^N
    while (N) {
        if (N & 1) multiply(res, A);
        multiply(A, A);
        N /= 2;
    }
    return 0;
}