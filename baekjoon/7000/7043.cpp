#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int mxN = 25e3;

p a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, T; cin >> N >> T;
    loop(i, N) cin >> a[i].first >> a[i].second;
    sort(a, a + N);

    int j = 0, ans = 0;
    for (int i = 0, v; j ^ T; j = v, ++ans) {
        v = 0;
        while (i ^ N && a[i].first <= j + 1)
            v = max(v, a[i++].second);
        if (v == 0) break;
    }
    if (j ^ T) ans = -1;
    cout << ans;
    return 0;
}