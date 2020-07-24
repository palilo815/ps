#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;

const int max_N = 1e5;
const int seg_N = 131072;

const int mod = 1e9 + 7;
const ll B[2][2] = {0, 1, 1, 1};

int f1[seg_N << 1], f2[seg_N << 1];
int lazy[seg_N << 1];
int mat[max_N][2][2];

int calc(int i, int j) {
    if (lazy[i]) return ((ll)mat[lazy[i]][j][0] * f1[i] + (ll)mat[lazy[i]][j][1] * f2[i]) % mod;
    return j ? f2[i] : f1[i];
}
void prop(int i) {
    int F1 = ((ll)mat[lazy[i]][0][0] * f1[i] + (ll)mat[lazy[i]][0][1] * f2[i]) % mod;
    int F2 = ((ll)mat[lazy[i]][1][0] * f1[i] + (ll)mat[lazy[i]][1][1] * f2[i]) % mod;
    f1[i] = F1, f2[i] = F2;
    if (i < seg_N) lazy[left] += lazy[i], lazy[right] += lazy[i];
    lazy[i] = 0;
}
void update(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {++lazy[i]; return;}
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    update(l, m, ql, qr, left), update(m, r, ql, qr, right);
    f1[i] = (calc(left, 0) + calc(right, 0)) % mod;
    f2[i] = (calc(left, 1) + calc(right, 1)) % mod;
}
int query(int l, int r, int ql, int qr, int i) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return calc(i, 0);
    if (lazy[i]) prop(i);

    int m = (l + r) >> 1;
    return (query(l, m, ql, qr, left) + query(m, r, ql, qr, right)) % mod;
}
void mul(int C[][2], int A[][2]) {
    loop(i, 2) loop(k, 2) loop(j, 2) {
        C[i][j] += A[i][k] * B[k][j] % mod;
        C[i][j] %= mod;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;

    fill_n(f2 + seg_N, N, 1);
    for (int i = seg_N - 1; i; --i)
        f2[i] = f2[left] + f2[right];

    mat[0][0][0] = 1, mat[0][1][1] = 1;
    loop(i, Q - 1) mul(mat[i + 1], mat[i]);

    for (int i = 0, l, r; i < Q; ++i) {
        char q; cin >> q >> l >> r; --l;
        if (q == 'D') update(0, seg_N, l, r, 1);
        else cout << query(0, seg_N, l, r, 1) << '\n';
    }
    return 0;
}