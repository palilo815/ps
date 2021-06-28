#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<int> sender(m);
    for (auto& x : sender) cin >> x;

    auto compress = [&]<typename T>(vector<T>& vt) -> int {
        vector<T> vals = vt;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        for (auto& x : vt)
            x = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
        return vals.size();
    };

    const int k = compress(sender);

    vector last_seen(k, -1);

    int64_t unread = 0;
    for (int i = 0; i < m; ++i) {
        unread += n - 1;
        unread -= i - exchange(last_seen[sender[i]], i) - 1;
        cout << unread << '\n';
    }
}