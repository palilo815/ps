#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;

const int max_N = 1e5;
const int NEG = 0xc0c0c0c0;

int N;
int st[max_N << 1];
int lt[max_N << 1];
int mt[max_N << 1];
int rt[max_N << 1];

void init() {
    cin >> N;
    for (int i = N; i < N << 1; ++i)
        cin >> st[i];

    copy(st + N, st + (N << 1), lt + N);
    copy(st + N, st + (N << 1), mt + N);
    copy(st + N, st + (N << 1), rt + N);

    for (int i = N - 1; i; --i) {
        st[i] = st[left] + st[right];
        lt[i] = max(lt[left], st[left] + lt[right]);
        mt[i] = max({mt[left], mt[right], rt[left] + lt[right]});
        rt[i] = max(rt[left] + st[right], rt[right]);
    }
}
int query(int u, int v) {
    int um, ur, vl, vm;
    um = ur = vl = vm = NEG;

    for (u += N, v += N; u < v; u >>= 1, v >>= 1) {
        if (u & 1) {
            um = max({um, mt[u], ur + lt[u]});
            ur = max(ur + st[u], rt[u]);
            ++u;
        }
        if (v & 1) {
            --v;
            vm = max({vm, mt[v], rt[v] + vl});
            vl = max(st[v] + vl, lt[v]);
        }
    }
    return max({um, ur + vl, vm});
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    init();

    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v;
        cout << query(--u, v) << '\n';
    }
    return 0;
}