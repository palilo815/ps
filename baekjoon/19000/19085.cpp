#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    constexpr int BLOCK = 1 << 12;
    constexpr int MX_NUM = 1e5 + 1;

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<bitset<MX_NUM>> block((n + BLOCK - 1) / BLOCK);
    for (int i = 0; i < n; ++i)
        block[i / BLOCK][a[i]].flip();

    bitset<MX_NUM> res;
    for (int q, op, l, r, ans;;) {
        cin >> q;
        if (!q) break;

        while (q--) {
            cin >> op >> l >> r, --l;
            if (op == 1) {
                block[l / BLOCK][a[l]].flip();
                a[l] = r;
                block[l / BLOCK][a[l]].flip();
            } else {
                res.reset();
                for (int i = l; i < r;) {
                    if (i % BLOCK == 0 && i + BLOCK <= r) {
                        res ^= block[i / BLOCK];
                        i += BLOCK;
                    } else
                        res[a[i++]].flip();
                }
                ans = res._Find_first();
                cout << (ans == MX_NUM ? -1 : ans) << '\n';
            }
        }
        cout << flush;
    }
}