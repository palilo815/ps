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
    cin.ignore();

    vector<pair<pair<int, int>, string>> a;
    unordered_map<string, int> mp;

    for (int i = 0; i < 3 * n; ++i) {
        string s;
        getline(cin, s);
        if (mp[s]) ++a[mp[s] - 1].first.first, a[mp[s] - 1].first.second = i;
        else {
            a.emplace_back(pair(1, i), s);
            mp[s] = a.size();
        }
    }

    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.first > rhs.first;
    });
    a.resize(min(a.size(), size_t(k)));

    for (const auto& [_, x] : a)
        cout << x << '\n';
}