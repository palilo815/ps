#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef struct {
    int A, B, C;
}ranking;

bool cmp(const ranking& x, const ranking& y) { return x.A < y.A; }

const int max_N = 500000;
ranking stdt[max_N];
int segT[524288 * 2 - 1];

void build_segT(int l, int r, int idx)
{
    segT[idx] = INT_MAX;
    if (l != r) {
        int m = l + (r - l) / 2;
        build_segT(l, m, 2 * idx + 1);
        build_segT(m + 1, r, 2 * idx + 2);
    }
}
void update(int qi, int qv, int l, int r, int idx)
{
    segT[idx] = min(segT[idx], qv);
    if (l == r) return;
    int m = l + (r - l) / 2;
    if (qi <= m) update(qi, qv, l, m, 2 * idx + 1);
    else update(qi, qv, m + 1, r, 2 * idx + 2);
}
int query(int ql, int qr, int l, int r, int idx)
{
    if (ql <= l && r <= qr) return segT[idx];
    if (qr < l || r < ql) return INT_MAX;
    int m = l + (r - l) / 2;
    return min(query(ql, qr, l, m, 2 * idx + 1), query(ql, qr, m + 1, r, 2 * idx + 2));
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) {
        int idx; cin >> idx;
        stdt[idx - 1].A = i;
    }
    loop(i, N) {
        int idx; cin >> idx;
        stdt[idx - 1].B = i;
    }
    loop(i, N) {
        int idx; cin >> idx;
        stdt[idx - 1].C = i;
    }
    sort(stdt, stdt + N, cmp);

    // A등수로 정렬
    build_segT(0, N - 1, 0);

    int ans = 0;
    loop(i, N) {
        // stdt[i] 순서에서 이미 segT에 들어가 있는 학생은
        // i보다 A시험을 잘 봤다.
        auto [a, b, c] = stdt[i];
        // [0,b]에 있는 학생은 i보다 B시험을 잘 봤다.
        int q = query(0, b, 0, N - 1, 0);
        // 만약 두 구간에 모두 속하는 학생 중
        // C시험도 i보다 잘 본 사람이 없다면 i는 굉장하다.
        if (q > c) ++ans;
        update(b, c, 0, N - 1, 0);
    }
    cout << ans;
    return 0;
}