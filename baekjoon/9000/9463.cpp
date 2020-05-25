#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 100001;

int N;
int A[max_N], B[max_N];
int fenwick[max_N];

void update(int i) {
    while (i <= N) {
        ++fenwick[i];
        i += i & -i;
    }
}
int query(int i) {
    int ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
start:;
    cin >> N;
    LOOP(i, N) cin >> A[i];
    LOOP(i, N) {
        int x; cin >> x;
        B[x] = i;
    }

    memset(fenwick + 1, 0, sizeof(int) * N);
    long long ans = 0;
    LOOP(i, N) {
        int v = B[A[i]];
        ans += query(N) - query(v);
        update(v);
    }
    cout << ans << '\n';
    if (--T) goto start;
    return 0;
}