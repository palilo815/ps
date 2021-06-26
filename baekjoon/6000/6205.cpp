#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int INF = 0x3f3f3f3f;

    int n, t;
    cin >> n >> t;

    vector<int> val(n);
    for (auto& x : val) cin >> x;

    const int mx_money = t + 1 + int(pow(*max_element(val.begin(), val.end()), 2));

    // {sum of values, # of coins}
    vector<pair<int, int>> items;
    for (int i = 0, c; i < n; ++i) {
        cin >> c;
        for (int cnt = 1; cnt <= c; cnt <<= 1) {
            items.emplace_back(val[i] * cnt, cnt);
            c -= cnt;
        }
        if (c) items.emplace_back(val[i] * c, c);
    }

    vector dp_rec(mx_money, INF);
    dp_rec[0] = 0;
    for (const auto& v : val)
        for (int i = v; i < mx_money; ++i)
            chmin(dp_rec[i], dp_rec[i - v] + 1);

    vector dp_pay(mx_money, INF);
    dp_pay[0] = 0;
    for (const auto& [sum, num] : items)
        for (int i = mx_money; i-- > sum;)
            chmin(dp_pay[i], dp_pay[i - sum] + num);

    int ans = INF;
    for (int i = t; i < mx_money; ++i)
        chmin(ans, dp_pay[i] + dp_rec[i - t]);
    cout << (ans == INF ? -1 : ans);
}