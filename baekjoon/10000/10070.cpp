#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;

const int seg_N = 2097152;

int minT[seg_N << 1], maxT[seg_N << 1];

void prop(int i) {
    for (int child : {left, right}) {
        if (maxT[child] <= minT[i]) minT[child] = maxT[child] = minT[i];
        else if (maxT[i] <= minT[child]) minT[child] = maxT[child] = maxT[i];
        else minT[child] = max(minT[child], minT[i]), maxT[child] = min(maxT[child], maxT[i]);
    }
}
void update(int l, int r, int op, int ql, int qr, int qv, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        if (op == 1) minT[i] = max(minT[i], qv), maxT[i] = max(maxT[i], qv);
        else minT[i] = min(minT[i], qv), maxT[i] = min(maxT[i], qv);
        return;
    }
    if (l + 1 ^ r) prop(i);

    int m = (l + r) >> 1;
    update(l, m, op, ql, qr, qv, left), update(m, r, op, ql, qr, qv, right);
    minT[i] = min(minT[left], minT[right]), maxT[i] = max(maxT[left], maxT[right]);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    for (int i = 0, op, l, r, v; i < Q; ++i) {
        cin >> op >> l >> r >> v; ++r;
        update(0, seg_N, op, l, r, v, 1);
    }

    for (int i = 1; i < seg_N; ++i)
        prop(i);

    for (int i = seg_N; i < seg_N + N; ++i)
        cout << minT[i] << '\n';
    return 0;
}