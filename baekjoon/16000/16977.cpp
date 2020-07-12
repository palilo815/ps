#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define x first
#define y second
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using p = pair<int, int>;
struct query {
    int u, v, w;
};

const int M = 1e5;
const int seg_N = 131072;

int N, lt[seg_N << 1], mt[seg_N << 1], rt[seg_N << 1];
p h[M];

query q[M];
int lo[M], hi[M];

void reset() {
    memset(lt, 0, sizeof(int) * (seg_N + N));
    memset(mt, 0, sizeof(int) * (seg_N + N));
    memset(rt, 0, sizeof(int) * (seg_N + N));
}
int query(int u, int v) {
    int um = 0, ur = 0, vl = 0, vm = 0, k = 1;
    for (u += seg_N, v += seg_N; u < v; u >>= 1, v >>= 1, k <<= 1) {
        if (u & 1) {
            um = max({um, mt[u], ur + lt[u]});
            ur = rt[u] + (rt[u] == k ? ur : 0);
            ++u;
        }
        if (v & 1) {
            --v;
            vm = max({vm, mt[v], vl + rt[v]});
            vl = lt[v] + (lt[v] == k ? vl : 0);
        }
    }
    return max({um, ur + vl, vm});
}
void update(int i) {
    i += seg_N;
    lt[i] = mt[i] = rt[i] = 1;
    i >>= 1;
    for (int k = 1; i; i >>= 1, k <<= 1) {
        lt[i] = lt[left] + (lt[left] == k ? lt[right] : 0);
        mt[i] = max({mt[left], mt[right], rt[left] + lt[right]});
        rt[i] = rt[right] + (rt[right] == k ? rt[left] : 0);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> h[i].x;
    loop(i, N) h[i].y = i;
    sort(h, h + N, greater<p>());

    int Q; cin >> Q;
    loop(i, Q) cin >> q[i].u >> q[i].v >> q[i].w;
    loop(i, Q) --q[i].u;
    fill_n(hi, Q, N);

    while (1) {
        vector<vector<int>> vt(N);
        bool done = true;

        loop(i, Q) if (lo[i] ^ hi[i]) {
            vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
            done = false;
        }
        if (done) break;

        reset();

        int j = 0;
        loop(m, N) {
            update(h[m].y);
            for (int& i : vt[m]) {
                int len = query(q[i].u, q[i].v);
                len < q[i].w ? (lo[i] = m + 1) : (hi[i] = m);
            }
        }
    }
    loop(i, Q) cout << h[lo[i]].x << '\n';
    return 0;
}