#include <bits/stdc++.h>
using namespace std;

struct depo {
    int r, c, f, need;
};

const int mxN = 1e3;

depo a[mxN + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int R, C, N;
    cin >> R >> C >> N;

    a[0].r = 1, a[0].c = 1;
    for (int i = 1; i <= N; ++i)
        cin >> a[i].r >> a[i].c >> a[i].f;
    for (int i = 0; i <= N; ++i)
        a[i].need = max(0, R - a[i].r + C - a[i].c - a[i].f);

    sort(a, a + N + 1, [](auto& a, auto& b) {
        return a.r == b.r ? a.c < b.c : a.r < b.r;
    });

    for (int i = N; ~i; --i)
        for (int j = i - 1; ~j; --j)
            if (a[j].c <= a[i].c)
                a[j].need = min(a[j].need, max(0, a[i].need + a[i].r - a[j].r + a[i].c - a[j].c - a[j].f));
    cout << a[0].need;
}