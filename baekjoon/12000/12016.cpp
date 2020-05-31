#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<N;++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> p;

const int max_N = 100000;

int N;
p job[max_N];
ll ans[max_N];
ll fenwick[max_N + 1];

void update(int i, int v) {
    for (++i; i <= N; i += i & -i)
        fenwick[i] += v;
}
ll read(int i) {
    ll ret = 0;
    for (++i; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> job[i].first, job[i].second = i;
    loop(i, N) update(i, 1);

    sort(job, job + N);
    ll psum = 0;
    loop(j, N) {
        auto [t, i] = job[j];
        ans[i] = psum + read(i) * t + (read(N - 1) - read(i)) * (t - 1);
        psum += t;
        update(i, -1);
    }
    loop(i, N) cout << ans[i] << '\n';
    return 0;
}