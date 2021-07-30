#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    auto b = a;
    sort(b.begin(), b.end());
    auto st = mismatch(a.begin(), a.end(), b.begin()).first;
    if (st == a.end()) {
        return cout << "1 1", 0;
    }
    auto ed = a.end() - (mismatch(a.rbegin(), a.rend(), b.rbegin()).first - a.rbegin());
    if (is_sorted(st, ed, greater())) {
        cout << st - a.begin() + 1 << ' ' << ed - a.begin();
    } else {
        cout << "impossible";
    }
}