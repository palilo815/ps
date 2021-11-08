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
    unordered_map<string, int> mp;
    for (string s; n--;) {
        cin >> s;
        if (int(s.size()) >= m) ++mp[s];
    }
    vector<pair<string, int>> a;
    for (const auto& e : mp) {
        a.emplace_back(e);
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        if (lhs.second != rhs.second) return lhs.second > rhs.second;
        if (lhs.first.size() != rhs.first.size()) return lhs.first.size() > rhs.first.size();
        return lhs < rhs;
    });
    for (const auto& [x, y] : a) {
        cout << x << '\n';
    }
}