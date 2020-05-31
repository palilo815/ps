#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;

int N;
int h[max_N];
int c[max_N];
int ans[max_N];
int fenwick[max_N + 1];

void update(int i) {
    for (++i; i <= N; i += i & -i)
        --fenwick[i];
}
int read(int i) {
    int ret = i++;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int bs(int v) {
    int l = 0, r = N;
    while (l < r) {
        int m = (l + r) / 2;
        read(m) < v ? l = (m + 1) : r = m;
    }
    return l;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> h[i];
    loop(i, N) cin >> c[i];
    sort(h, h + N);

    for (int i = N - 1; i >= 0; --i) {
        int idx = bs(c[i]);
        ans[i] = h[idx];
        update(idx);
    }
    loop(i, N) cout << ans[i] << '\n';
    return 0;
}