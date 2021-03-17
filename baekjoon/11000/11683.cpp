#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    auto mex = [&](vector<int>& vt) {
        sort(vt.begin(), vt.end());
        vt.erase(unique(vt.begin(), vt.end()), vt.end());
        int ret = 0;
        for (const auto& x : vt) {
            if (ret != x) return ret;
            ++ret;
        }
        return ret;
    };

    int p, k;
    cin >> p >> k;

    int xorsum = 0;
    for (int n; p--;) {
        cin >> n;
        vector<int> card(n);
        for (auto& x : card)
            cin >> x;

        vector<int> grundy(n + 1);
        for (int i = 1; i <= n; ++i) {
            vector<int> vt;
            for (int rem = 0; rem <= k && rem < i; ++rem) {
                int nxt = i - rem - card[i - rem - 1];
                // nxt장 남긴다.
                if (nxt >= 0) vt.emplace_back(grundy[nxt]);
            }
            grundy[i] = mex(vt);
        }
        xorsum ^= grundy[n];
        cout << grundy[n] << '\n';
    }
    cout << (xorsum ? "Alice can win." : "Bob will win.");
}