#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k, --k;
    vector<int> vt {0};
    array<bool, 32> buf;
    for (int i = 1; int(vt.size()) < 5 * n; ++i) {
        int len = 0;
        for (int j = i; j; j >>= 1) {
            buf[len++] = j & 1;
        }
        while (len--) {
            vt.emplace_back(buf[len]);
        }
    }
    for (int i = 0; i < 5; ++i) {
        cout << vt[i * n + k] << ' ';
    }
}