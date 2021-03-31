#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int mxN = 1e6;

    array<bool, mxN + 1> win {};
    for (int i = 0; i < mxN; ++i)
        if (!win[i])
            for (int j = 1; i + j * j <= mxN; ++j)
                win[i + j * j] = true;

    int t;
    cin >> t;

    for (int n; t--;) {
        cin >> n;
        cout << (win[n] ? "koosaga\n" : "cubelover\n");
    }
}