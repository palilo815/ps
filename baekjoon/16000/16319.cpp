#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, d;
    cin >> n >> m >> d;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> b(m);
    for (auto& x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int initial = 0;
    for (int i = m; i--;) initial = initial * 7 + b[i];
    for (int i = n; i--;) initial = initial * 7 + a[i];

    int live;
    vector<int> hp(n + m);
    auto get_hp = [&](int mask) -> void {
        for (auto& x : hp) {
            x = mask % 7;
            mask /= 7;
        }

        live = 0;
        for (const auto x : hp)
            live += !!x;
    };

    constexpr array offset = {1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607, 282475249};

    // {mask, probability}
    unordered_map<int, double> dp, prv;
    dp[initial] = 1.0;

    unordered_set<int> pushed;

    queue<int> q;
    q.emplace(initial);

    for (int dmg = 0; dmg < d; ++dmg) {
        dp.swap(prv);
        dp.clear();

        auto q_size = q.size();
        while (q_size--) {
            const auto mask = q.front();
            q.pop();

            get_hp(mask);

            for (int i = 0, j; i < n; ++i) {
                if (!hp[i]) continue;
                for (j = i + 1; j < n && hp[i] == hp[j]; ++j)
                    ;
                auto nxt = mask - offset[i];
                dp[nxt] += prv[mask] * (j - i) / live;
                if (!pushed.count(nxt)) {
                    pushed.emplace(nxt);
                    q.emplace(nxt);
                }
                i = j - 1;
            }
            for (int i = n, j; i < n + m; ++i) {
                if (!hp[i]) continue;
                for (j = i + 1; j < n + m && hp[i] == hp[j]; ++j)
                    ;
                auto nxt = mask - offset[i];
                dp[nxt] += prv[mask] * (j - i) / live;
                if (!pushed.count(nxt)) {
                    pushed.emplace(nxt);
                    q.emplace(nxt);
                }
                i = j - 1;
            }
        }
    }

    double ans = dp.empty();
    for (const auto [mask, p] : dp)
        if (mask < offset[n])
            ans += p;
    cout << fixed << setprecision(9) << ans;
}