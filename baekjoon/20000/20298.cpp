#include <algorithm>
#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> s(n << 1), k(m);
    for (int i {}; i < n; ++i) {
        cin >> s[i];
    }
    for (auto& x : k) {
        cin >> x;
    }
    copy(s.begin(), s.begin() + n, s.begin() + n);
    const auto comp_sz {[&]() {
        auto comp {k};
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for (auto& x : k) {
            x = lower_bound(comp.begin(), comp.end(), x) - comp.begin();
        }
        return comp.size();
    }()};
    vector<int> l(m), r(m), c(m);
    {
        vector<int> prv(comp_sz), nxt(comp_sz);
        iota(prv.begin(), prv.end(), -1);
        iota(nxt.begin(), nxt.end(), 1);
        nxt.back() = -1;
        vector<forward_list<int>> indice(comp_sz);
        for (int i {}; i < m; ++i) {
            indice[k[i]].emplace_front(i);
        }
        for (auto i {m}; i--;) {
            if (~prv[k[i]]) l[i] = i - indice[prv[k[i]]].front();
            if (~nxt[k[i]]) r[i] = i - indice[nxt[k[i]]].front();
            indice[k[i]].pop_front();
            if (indice[k[i]].empty()) {
                if (~prv[k[i]]) nxt[prv[k[i]]] = nxt[k[i]];
                if (~nxt[k[i]]) prv[nxt[k[i]]] = prv[k[i]];
            } else {
                c[i] = i - indice[k[i]].front();
            }
        }
    }
    auto ok = [&](const int* value, int j) {
        return (!l[j] || *value > *(value - l[j])) &&
               (!r[j] || *value < *(value - r[j])) &&
               (!c[j] || *value == *(value - c[j]));
    };
    vector<int> pi(m);
    for (int i {1}, j {}; i < m; ++i) {
        while (j && !ok(&k[i], j)) j = pi[j - 1];
        if (ok(&k[i], j)) pi[i] = ++j;
    }
    int ans {};
    for (int i {}, j {}; i < n + m - 1; ++i) {
        while (j && !ok(&s[i], j)) j = pi[j - 1];
        if (ok(&s[i], j) && ++j == m) {
            ++ans;
            j = pi[j - 1];
        }
    }
    cout << ans;
}
