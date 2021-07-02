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
    for (auto& x : a) cin >> x;

    const auto total = accumulate(a.begin(), a.end(), 0);

    if (total & 1)
        return cout << 'N', 0;

    int cnt = 0;
    for (int i = 0, j = 0, sum = 0; i < n;) {
        if (sum * 2 < total) {
            sum += a[j];
            j = j == n - 1 ? 0 : j + 1;
        } else if (sum * 2 > total) {
            sum -= a[i++];
        } else {
            sum -= a[i++];
            ++cnt;
        }
    }
    cout << (cnt >= 4 ? 'Y' : 'N');
}