#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;
struct gold {
    int x, y, w;
};

const int max_N = 3e3;
const int seg_N = 32768;

int N, M, idx[max_N];
gold a[max_N + 1];
ll st[seg_N << 1], lt[seg_N << 1], mt[seg_N << 1], rt[seg_N << 1];

void reset() {
    memset(st, 0, sizeof(ll) * (seg_N + M));
    memset(lt, 0, sizeof(ll) * (seg_N + M));
    memset(mt, 0, sizeof(ll) * (seg_N + M));
    memset(rt, 0, sizeof(ll) * (seg_N + M));
}
void update(int i, int v) {
    i += seg_N;
    st[i] += v, lt[i] += v, mt[i] += v, rt[i] += v;
    for (i >>= 1; i; i >>= 1) {
        st[i] = st[left] + st[right];
        lt[i] = max(lt[left], st[left] + lt[right]);
        mt[i] = max({mt[left], mt[right], rt[left] + lt[right]});
        rt[i] = max(rt[right], st[right] + rt[left]);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> a[i].x >> a[i].y >> a[i].w;
    a[N].y = INT_MAX;

    loop(i, N) idx[i] = a[i].x;
    sort(idx, idx + N);
    M = unique(idx, idx + N) - idx;

    loop(i, N) a[i].x = lower_bound(idx, idx + M, a[i].x) - idx;
    sort(a, a + N, [&](gold & a, gold & b) -> bool {
        return a.y < b.y;
    });

    ll ans = 0;
    loop(i, N) {
        reset();
        for (int j = i; j < N; ++j) {
            update(a[j].x, a[j].w);
            if (a[j].y ^ a[j + 1].y) ans = max(ans, mt[1]);
        }
        while (a[i].y == a[i + 1].y) ++i;
    }
    cout << ans;
    return 0;
}