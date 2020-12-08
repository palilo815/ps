#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct snow {
    int h, i;
};
struct boot {
    int s, d, i;
};

snow a[mxN + 1];
boot b[mxN];
int l[mxN], r[mxN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, B;
    cin >> N >> B;

    for (int i = 0; i < N; ++i) {
        cin >> a[i].h;
        a[i].i = i;
    }
    for (int i = 0; i < B; ++i) {
        cin >> b[i].s >> b[i].d;
        b[i].i = i;
    }

    sort(a, a + N, [&](auto& a, auto& b) {
        return a.h > b.h;
    });
    sort(b, b + B, [&](auto& a, auto& b) {
        return a.s > b.s;
    });

    iota(l, l + N, -1);
    iota(r, r + N, 1);

    vector<bool> ans(B);
    for (int i = 0, j = 0, mx = 1; i < B; ++i) {
        // a[N] is sentinel
        for (; a[j].h > b[i].s; ++j) {
            mx = max(mx, r[a[j].i] - l[a[j].i]);
            l[r[a[j].i]] = l[a[j].i];
            r[l[a[j].i]] = r[a[j].i];
        }
        ans[b[i].i] = mx <= b[i].d;
    }

    for (auto x : ans)
        cout << x << '\n';
}