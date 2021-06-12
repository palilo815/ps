#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int SZ = 512;

    int n, m, k;
    cin >> n >> m >> k;

    bitset<SZ * SZ> sea;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            char c;
            cin >> c;
            sea[i * (m + 2) + j] = c == '.';
        }

    auto ok = sea;

    string s;
    cin >> s;

    for (const auto& c : s) {
        if (c == 'E')
            ok <<= 1;
        else if (c == 'W')
            ok >>= 1;
        else if (c == 'S')
            ok <<= m + 2;
        else if (c == 'N')
            ok >>= m + 2;
        else
            ok = (ok << 1) | (ok >> 1) | (ok << (m + 2)) | (ok >> (m + 2));
        ok &= sea;
    }

    cout << ok.count();
}