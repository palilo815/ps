#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, M;
    cin >> N >> M;

    vector<int> vt;
    unordered_map<string, int> price;
    while (N--) {
        string s;
        int p;
        cin >> s >> p;
        price[s] = p;
        vt.emplace_back(p);
    }

    int k = 0, ans = 0;
    while (M--) {
        string s;
        cin >> s;
        if (s == "?") ++k;
        else {
            auto it = find(vt.begin(), vt.end(), price[s]);
            ans += *it;
            *it = -1;
        }
    }

    vt.resize(remove_if(vt.begin(), vt.end(), [&](auto& x) { return x == -1; }) - vt.begin());
    sort(vt.begin(), vt.end());

    cout << ans + accumulate(vt.begin(), vt.begin() + k, 0) << ' ' << ans + accumulate(vt.end() - k, vt.end(), 0) << '\n'
         << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Data Set " << t << ":\n";
        solve();
    }
    return 0;
}