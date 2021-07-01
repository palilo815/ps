#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    string u, v;
    cin >> n >> u >> v;

    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans += u[i] == v[i];
    cout << ans;
}