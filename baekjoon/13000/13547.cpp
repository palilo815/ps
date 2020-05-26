#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int sqrt_N;
struct _query {
    int i, s, e;
    bool operator <(_query& b) {
        int A = s / sqrt_N, B = b.s / sqrt_N;
        return A == B ? e < b.e : A < B;
    }
};

const int max_N = 100001;
const int max_A = 1000001;

int A[max_N];
int ans[max_N];
int cnt[max_A];
_query query[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    int Q; cin >> Q;
    loop(i, Q) {
        query[i].i = i;
        cin >> query[i].s >> query[i].e;
    }

    sqrt_N = sqrt(N);
    sort(query, query + Q);

    int res = 0;
    int s = query[0].s, e = query[0].e;
    for (int i = s; i <= e; ++i)
        res += (++cnt[A[i]] == 1);
    ans[query[0].i] = res;

    for (int i = 1; i < Q; ++i) {
        auto& [I, S, E] = query[i];
        while (s < S) res -= (--cnt[A[s++]] == 0);
        while (s > S) res += (++cnt[A[--s]] == 1);
        while (e < E) res += (++cnt[A[++e]] == 1);
        while (e > E) res -= (--cnt[A[e--]] == 0);
        ans[I] = res;
    }

    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}