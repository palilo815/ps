#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

//const int max_N = 1e6;
const int max_N = 1e2;

int N, Q[max_N], id[max_N << 1];
p query[max_N];
int fenwick[max_N << 1 | 1];

void update(int i) {
    for (++i; i <= N; i += i & -i)
        ++fenwick[i];
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N0; cin >> N0;
    loop(i, N0) cin >> Q[i];
    copy(Q, Q + N0, id);
    N = N0;

    int M; cin >> M;
    loop(i, M) {
        auto& [x, y] = query[i];
        int q; cin >> q;
        if (q == 1) {
            cin >> x;
            id[N++] = x;
            y = INT_MAX;
        }
        else cin >> x >> y;
    }

    sort(id, id + N);
    loop(i, N0) update(lower_bound(id, id + N, Q[i]) - id);

    loop(i, M) {
        auto& [x, y] = query[i];
        if (y == INT_MAX) update(lower_bound(id, id + N, x) - id);
        else cout << y - x + 1 - read(upper_bound(id, id + N, y) - id)
                      + read(lower_bound(id, id + N, x) - id) << '\n';
    }
    return 0;
}