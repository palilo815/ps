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
    partial_sum(a.begin(), a.end(), a.begin());
    if (a.back() % 4) {
        return cout << 0, 0;
    }
    const int block = a.back() / 4;
    if (block) {
        array<int64_t, 4> cnt {};
        cnt[0] = 1;
        for (const auto& x : a) {
            if (x == 0 || x % block || x / block == 4) {
                continue;
            }
            cnt[x / block] += cnt[x / block - 1];
        }
        cout << cnt[3] << '\n';
    } else {
        int64_t zero = count(a.begin(), a.end(), 0) - 1;
        cout << zero * (zero - 1) * (zero - 2) / 3 / 2;
    }
}