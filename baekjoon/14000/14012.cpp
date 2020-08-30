#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e5;

int a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> a[i];

    vector<pair<int, int>> vt;
    loop(i, N) {
        int b; cin >> b;
        if (a[i] < b) vt.emplace_back(a[i], b - a[i]);
    }

    sort(vt.begin(), vt.end(), [&](auto & a, auto & b) {
        return a.first < b.first;
    });

    long long ans = M;
    for (auto& [need, earn] : vt) {
        if (ans < need) break;
        ans += earn;
    }
    cout << ans;
    return 0;
}