#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t x;
    cin >> n >> x;
    vector<int64_t> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    transform(a.begin(), a.end(), a.begin(), [&](const auto& x) {
        return x << 1;
    });
    sort(a.begin(), a.end());
    int ans = 0;
    while (!a.empty() && a.back() == (x << 1)) {
        ++ans, a.pop_back();
    }
    n = a.size();
    for (auto lptr = a.begin(), rptr = prev(a.end());; ++lptr, --rptr, ++ans, n -= 2) {
        while (lptr < rptr && *lptr + *rptr < x) ++lptr;
        if (!(lptr < rptr)) break;
    }
    cout << ans + n / 3;
}