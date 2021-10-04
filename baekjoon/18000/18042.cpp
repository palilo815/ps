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
    auto ptr = a.begin();
    priority_queue<int> pq;
    while (ptr != a.end() && *ptr <= k) {
        pq.emplace(*ptr++);
    }
    auto sum = accumulate(a.begin(), a.end(), int64_t(0));
    for (int i = 0;; ++i) {
        if (k >= sum) {
            cout << i << '\n';
            return;
        }
        if (pq.empty()) {
            cout << "-1\n";
            return;
        }
        k += pq.top(), sum -= pq.top();
        pq.pop();
        while (ptr != a.end() && *ptr <= k) {
            pq.emplace(*ptr++);
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