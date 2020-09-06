#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct cow {
    int x, b;
};

const int mxN = 1e6;

cow a[mxN];
int table[mxN << 1 | 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i].b >> a[i].x;
    loop(i, N) if (!a[i].b) a[i].b = -1;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.x < b.x;
    });

    int s = mxN, ans = 0;
    loop(i, N) {
        if (!table[s]) table[s] = a[i].x + 1;
        s += a[i].b;
        if (table[s]) ans = max(ans, a[i].x + 1 - table[s]);
    }
    cout << ans;
    return 0;
}