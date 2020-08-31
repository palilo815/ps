#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using p = pair<int, int>;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int L, N, rf, rb;
    cin >> L >> N >> rf >> rb;
    rf -= rb;

    vector<p> rest;
    for (int i = 0, x, c; i < N; ++i) {
        cin >> x >> c;
        while (!rest.empty() && rest.back().second < c)
            rest.pop_back();
        rest.emplace_back(x, c);
    }

    ll pos = 0, ans = 0;
    for (auto& [x, c] : rest) {
        ans += (x - pos) * rf * c;
        pos = x;
    }
    cout << ans;
    return 0;
}