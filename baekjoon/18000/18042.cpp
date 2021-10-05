#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    auto sum = accumulate(a.begin(), a.end(), int64_t(0));
    auto ptr = find_if(a.begin(), a.end(), [&](const auto& x) {
        return x > k;
    });
    auto top = ptr;
    for (int i = 0;; ++i) {
        if (k >= sum) {
            cout << i << '\n';
            return;
        }
        if (top == a.begin()) {
            cout << "-1\n";
            return;
        }
        --top;
        k += *top, sum -= *top;
        for (; ptr != a.end() && *ptr <= k; ++top, ++ptr) {
            *top = *ptr;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) solve();
}