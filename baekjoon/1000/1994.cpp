#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 2000;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i];
    sort(a, a + N);

    int ans = 1, cnt = 1, M = 1;
    for (int i = 1; i < N; ++i) {
        if (a[i] == a[i - 1])
            ans = max(ans, ++cnt);
        else cnt = 1, a[M++] = a[i];
    }

    loop(i, M - 1) for (int j = i + 1; j < M; ++j) {
        cnt = 2;
        for (int d = a[j] - a[i], k = j;; ++cnt) {
            int key = a[k] + d;
            k = lower_bound(a + k + 1, a + M, key) - a;
            if (k == M || a[k] != key) break;
        }
        if (cnt > ans) ans = cnt;
    }
    cout << ans;
    return 0;
}