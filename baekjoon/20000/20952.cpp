#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    array<int, 7> cnt {};
    for (const auto& x : a)
        ++cnt[x % 7];

    int total = n;
    int64_t added = 0;
    for (int x; m--;) {
        cin >> x;
        added += x;
        int target = added % 7 ? 7 - added % 7 : 0;
        if (cnt[target] == total) added -= x;
        else {
            total -= cnt[target];
            cnt[target] = 0;
        }
    }

    a.resize(remove_if(a.begin(), a.end(), [&](auto& x) { return !cnt[x % 7]; }) - a.begin());

    cout << a.size() << '\n';
    for (auto& x : a)
        cout << (x + added) % mod << ' ';
}