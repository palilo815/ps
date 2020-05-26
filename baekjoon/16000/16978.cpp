#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
struct _1_query {
    int i, v;
};
struct _2_query {
    int qi, l, r, idx;
};

const int max_N = 100000;

int N;
int arr[max_N];
ll fenwick[max_N + 1];
_1_query q1[max_N];
_2_query q2[max_N];
ll ans[max_N];

bool cmp(_2_query& a, _2_query& b) {
    return a.qi < b.qi;
}
void update(int i, int v) {
    int dv = v - arr[i - 1];
    arr[i - 1] = v;
    while (i <= N) {
        fenwick[i] += dv;
        i += i & -i;
    }
}
ll read(int i) {
    ll ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) {
        int x; cin >> x;
        update(i + 1, x);
    }
    int Q; cin >> Q;
    int q1_N = 0, q2_N = 0;
    loop(i, Q) {
        int n; cin >> n;
        if (n == 1) {
            auto& [i, v] = q1[q1_N++];
            cin >> i >> v;
        }
        else {
            auto& [qi, l, r, idx] = q2[q2_N];
            cin >> qi >> l >> r;
            idx = q2_N++;
        }
    }
    sort(q2, q2 + q2_N, cmp);

    int applied = 0;
    loop(i, q2_N) {
        auto& [qi, l, r, idx] = q2[i];
        while (applied < qi) {
            update(q1[applied].i, q1[applied].v);
            ++applied;
        }
        ans[idx] = read(r) - read(l - 1);
    }
    loop(i, q2_N) cout << ans[i] << '\n';
    return 0;
}