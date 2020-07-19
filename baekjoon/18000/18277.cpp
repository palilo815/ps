#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
struct query {
    int l, r, i;
    query(int l, int r, int i): l(l), r(r), i(i) {}
};

const int M = 3e4;
const int seg_N = 32768;
const int max_sq = 174;
const int POS = 0x3f3f3f3f;
const int NEG = 0xc0c0c0c0;

int a[M], ans[M];
int segT[seg_N << 1], lt[seg_N << 1], rt[seg_N << 1];
vector<query> q[max_sq];

void init() {
    memset(lt, POS, sizeof(lt));
    memset(rt, NEG, sizeof(rt));
    memset(segT, POS, sizeof(int) * seg_N);
}
void update(int i, int f) {
    i += seg_N;
    if (f) lt[i] = rt[i] = i - seg_N;
    else lt[i] = POS, rt[i] = NEG;

    for (i >>= 1; i; i >>= 1) {
        lt[i] = (lt[left] == POS ? lt[right] : lt[left]);
        rt[i] = (rt[right] == NEG ? rt[left] : rt[right]);
        segT[i] = min({segT[left], segT[right], lt[right] - rt[left]});
    }
}
void solve(vector<query>& q, int s) {
    init();
    sort(q.begin(), q.end(), [&](auto & a, auto & b) -> bool {
        return a.r == b.r ? a.l < b.l : a.r < b.r;
    });

    int l = s, r = s + 1;
    update(a[s], 1);
    for (auto& [L, R, i] : q) {
        while (L < l) update(a[--l], 1);
        while (r < R) update(a[r++], 1);
        while (l < L) update(a[l++], 0);
        while (R < r) update(a[--r], 0);
        ans[i] = segT[1];
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    loop(i, N) cin >> a[i];
    loop(i, N) --a[i];

    int sq = sqrt(N - 1) + 1;
    loop(i, Q) {
        int l, r; cin >> l >> r;
        --l;
        q[l / sq].emplace_back(l, r, i);
    }

    memset(segT + seg_N, POS, sizeof(int) * seg_N);
    loop(i, sq + 1) if (!q[i].empty())
        solve(q[i], i * sq);

    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}