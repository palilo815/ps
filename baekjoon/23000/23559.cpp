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
    m = (m / 1000 - n) >> 2;
    vector<int> more(n);
    int ans = 0;
    for (auto& x : more) {
        int a, b;
        cin >> a >> b;
        ans += b;
        x = max(0, a - b);
    }
    sort(more.begin(), more.end(), greater());
    cout << ans + accumulate(more.begin(), more.begin() + m, 0);
}