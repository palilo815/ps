#include <bits/stdc++.h>
using namespace std;

struct rook {
    int r, c, x;
};

struct elem {
    int r1, c1, r2, c2;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k, p;
    cin >> n >> k >> p;

    vector<rook> a(k);
    for (auto& [r, c, x] : a) cin >> r >> c >> x;

    vector<elem> mv(p);
    for (auto& [r1, c1, r2, c2] : mv) cin >> r1 >> c1 >> r2 >> c2;

    vector<int> ordR(k + p), ordC(k + p);
    for (int i = 0; i < k; ++i)
        ordR[i] = a[i].r, ordC[i] = a[i].c;
    for (int i = 0; i < p; ++i)
        ordR[k + i] = mv[i].r2, ordC[k + i] = mv[i].c2;

    sort(ordR.begin(), ordR.end());
    sort(ordC.begin(), ordC.end());
    ordR.erase(unique(ordR.begin(), ordR.end()), ordR.end());
    ordC.erase(unique(ordC.begin(), ordC.end()), ordC.end());

    for (auto& [r, c, _] : a)
        r = lower_bound(ordR.begin(), ordR.end(), r) - ordR.begin(),
        c = lower_bound(ordC.begin(), ordC.end(), c) - ordC.begin();
    for (auto& [r1, c1, r2, c2] : mv)
        r1 = lower_bound(ordR.begin(), ordR.end(), r1) - ordR.begin(),
        c1 = lower_bound(ordC.begin(), ordC.end(), c1) - ordC.begin(),
        r2 = lower_bound(ordR.begin(), ordR.end(), r2) - ordR.begin(),
        c2 = lower_bound(ordC.begin(), ordC.end(), c2) - ordC.begin();

    unordered_map<int64_t, int> mp;                   // mp[r << 32 | c][x] = [r][c]에 있는 rook의 x값
    vector<int> xorR(ordR.size()), xorC(ordC.size()); // xorR[i] = row_i에 있는 모든 rook의 xor값
    unordered_map<int, int> cntR, cntC;               // cntR[i] = xor값이 i인 row의 개수

    decltype(ordR)().swap(ordR);
    decltype(ordC)().swap(ordC);

    int64_t ans = 0;
    auto place = [&](int r, int c, int x) {
        ans += cntC[xorR[r]] + cntR[xorC[c]] - (xorR[r] == xorC[c]);

        --cntR[xorR[r]], --cntC[xorC[c]];
        xorR[r] ^= x, xorC[c] ^= x;
        ++cntR[xorR[r]], ++cntC[xorC[c]];

        ans -= cntC[xorR[r]] + cntR[xorC[c]] - (xorR[r] == xorC[c]);
    };

    cntR[0] = cntC[0] = n;
    for (const auto& [r, c, x] : a) {
        place(r, c, x);
        mp[int64_t(r) << 32 | c] = x;
    }
    for (const auto& [r1, c1, r2, c2] : mv) {
        const int x = mp[int64_t(r1) << 32 | c1];
        place(r1, c1, x);
        place(r2, c2, x);
        mp[int64_t(r2) << 32 | c2] = x;
        cout << ans << '\n';
    }
}