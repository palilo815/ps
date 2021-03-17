#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<int> cnt(n + m + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            ++cnt[i + j];

    auto mx = *max_element(cnt.begin(), cnt.end());
    for (int i = 0; i <= n + m; ++i)
        if (cnt[i] == mx)
            cout << i << '\n';
}