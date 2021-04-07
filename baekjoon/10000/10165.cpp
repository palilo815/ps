#include <bits/stdc++.h>
using namespace std;

struct elem {
    int s, e, id;
    elem(int s, int e, int id) : s(s), e(e), id(id) {}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<elem> a;
    a.reserve(m << 1);

    for (int i = 0, s, e; i < m; ++i) {
        cin >> s >> e, ++e;
        if (s < e)
            a.emplace_back(s, e, i), a.emplace_back(s + n, e + n, i);
        else
            a.emplace_back(s, e + n, i);
    }

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.s == b.s ? a.e > b.e : a.s < b.s;
    });

    vector<bool> useless(m);
    int prv = -1;
    for (const auto& [s, e, id] : a)
        prv < e ? prv = e : useless[id] = true;

    for (int i = 0; i < m; ++i)
        if (!useless[i])
            cout << i + 1 << ' ';
}