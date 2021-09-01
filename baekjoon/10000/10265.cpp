#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> nxt(n);
    for (auto& x : nxt) {
        cin >> x, --x;
    }
    vector<vector<int>> rev(n);
    for (int i = 0; i < n; ++i) {
        rev[nxt[i]].emplace_back(i);
    }
    vector colour(n, -1); // -1: white, -2: grey, -3: black, etc: id of cycle
    vector<int> cycle_size, stk;
    for (int i = 0; i < n; ++i) {
        if (~colour[i]) continue;
        int u = i;
        for (stk.clear(); colour[u] == -1; u = nxt[u]) {
            stk.emplace_back(u);
            colour[u] = -2;
        }
        if (colour[u] == -2) {
            auto st = find(stk.begin(), stk.end(), u);
            assert(st != stk.end());
            for_each(st, stk.end(), [&](const auto& x) { colour[x] = cycle_size.size(); });
            cycle_size.emplace_back(stk.end() - st);
            stk.erase(st, stk.end());
        }
        for (const auto& x : stk) {
            colour[x] = -3;
        }
    }
    vector<bool> dp(k + 1), prv(k + 1);
    dp[0] = true;
    for (int i = 0; i < int(cycle_size.size()); ++i) {
        stk.clear();
        for (int u = 0; u < n; ++u) {
            if (colour[u] == i) {
                colour[u] = -1;
                stk.emplace_back(u);
            }
        }
        const auto mn = cycle_size[i];
        auto mx = mn;
        while (!stk.empty()) {
            const auto u = stk.back();
            stk.pop_back();
            for (const auto& v : rev[u]) {
                if (~colour[v]) {
                    colour[v] = -1;
                    ++mx;
                    stk.emplace_back(v);
                }
            }
        }
        copy(dp.begin(), dp.end(), prv.begin());
        for (int i = 0; i < k; ++i) {
            if (prv[i]) {
                for (int it = i + mn, ed = min(k, i + mx) + 1; it < ed; ++it) {
                    dp[it] = true;
                }
            }
        }
    }
    cout << dp.rend() - find(dp.rbegin(), dp.rend(), true) - 1;
}