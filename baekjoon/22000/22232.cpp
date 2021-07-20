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
    vector<string> a(n), ext(m);
    for (auto& x : a) {
        cin >> x;
    }
    for (auto& x : ext) {
        cin >> x;
    }
    sort(ext.begin(), ext.end());
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        const auto l_dot = lhs.find('.');
        const auto r_dot = rhs.find('.');
        const auto l_file = lhs.substr(0, l_dot);
        const auto r_file = rhs.substr(0, r_dot);
        if (l_file != r_file) {
            return l_file < r_file;
        }
        const auto l_is = binary_search(ext.begin(), ext.end(), lhs.substr(l_dot + 1));
        const auto r_is = binary_search(ext.begin(), ext.end(), rhs.substr(r_dot + 1));
        if (l_is ^ r_is) {
            return l_is;
        }
        return lhs.substr(l_dot + 1) < rhs.substr(r_dot + 1);
    });
    for (const auto& x : a) {
        cout << x << '\n';
    }
}