#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e5 - 1;

int d1[mxN], d2[mxN], p1[mxN], p2[mxN];

void solve() {
    int N, l1, l2, s1, s2;
    cin >> N >> l1 >> l2 >> s1 >> s2;

    --N;
    loop(i, N) cin >> p1[i];
    loop(i, N) cin >> d1[i];
    loop(i, N) cin >> p2[i];
    loop(i, N) cin >> d2[i];

    loop(i, N) {
        int nxt1 = min(l1 + d1[i], l2 + p2[i]);
        int nxt2 = min(l2 + d2[i], l1 + p1[i]);
        l1 = nxt1, l2 = nxt2;
    }

    cout << min(l1 + s1, l2 + s2) << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}