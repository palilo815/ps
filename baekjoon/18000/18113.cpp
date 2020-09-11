#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e6;

int N, M, a[mxN];

bool solve(int m) {
    int cnt = 0;
    loop(i, N) if ((cnt += a[i] / m) >= M)
        return true;
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K; cin >> N >> K >> M;
    loop(i, N) cin >> a[i];
    loop(i, N) {
        if (a[i] >= K * 2) a[i] -= K * 2;
        else if (a[i] > K) a[i] -= K;
        else a[i] = 0;
    }

    if (accumulate(a, a + N, 0LL) < M) {
        cout << -1;
        return 0;
    }

    int l = 1, r = *max_element(a, a + N);
    while (l ^ r) {
        int m = (l + r + 1) >> 1;
        solve(m) ? (l = m) : (r = m - 1);
    }
    cout << l;
    return 0;
}