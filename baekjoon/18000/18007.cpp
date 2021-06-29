#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int mod = 11092019;

    string s;
    cin >> s;

    array<int, 26> cnt {};
    for (const auto& c : s)
        ++cnt[c - 'a'];

    cout << accumulate(cnt.begin(), cnt.end(), 1ll, [&](const auto& sum, const auto& x) {
        return sum * (x + 1) % mod;
    });
}