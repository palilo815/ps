#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    string alpha, s;
    cin >> alpha >> s;

    set<string> ans;

    for (int i = 0; i <= int(s.size()); ++i)
        for (const auto& c : alpha)
            ans.emplace(string(s).insert(i, 1, c));

    for (int i = 0; i < int(s.size()); ++i)
        ans.emplace(string(s).erase(i, 1));

    for (auto& u : s) {
        const auto original = u;
        for (const auto& v : alpha)
            if (original != v) {
                u = v;
                ans.emplace(s);
            }
        u = original;
    }

    for (const auto& x : ans)
        cout << x << '\n';
}