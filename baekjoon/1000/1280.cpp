#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 2e5;
const int mod = 1e9 + 7;

int cntT[mxN + 1];
ll sumT[mxN + 1];

void u_cnt(int i) {
    for (; i <= mxN; i += i & -i)
        ++cntT[i];
}
int q_cnt(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += cntT[i];
    return ret;
}
void u_sum(int i, int val) {
    for (; i <= mxN; i += i & -i)
        sumT[i] += val;
}
ll q_sum(int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += sumT[i];
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    ll ans = 1, sum, cnt, total;
    for (int i = 1, x; i <= N; ++i) {
        cin >> x;
        ++x;
        if (i != 1) {
            sum = q_sum(x - 1), cnt = q_cnt(x - 1);
            total = (x * cnt - sum) % mod;

            sum = q_sum(mxN) - q_sum(x), cnt = q_cnt(mxN) - q_cnt(x);
            total = ((sum - x * cnt) % mod + total) % mod;

            ans = ans * total % mod;
        }
        u_cnt(x), u_sum(x, x);
    }
    cout << ans;
}