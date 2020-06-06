#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_K = 10000;

int N, K, D;
int rule[max_K][3];

ll solve(int num) {
    ll ret = 0;
    loop(i, K) if (num >= rule[i][0])
        ret += (min(num, rule[i][1]) - rule[i][0]) / rule[i][2] + 1;
    return ret;
}
int bs(int l, int r) {
    while (l < r) {
        int m = (l + r) >> 1;
        solve(m) < D ? (l = m + 1) : (r = m);
    }
    return l;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> K >> D;
    loop(i, K) cin >> rule[i][0] >> rule[i][1] >> rule[i][2];
    cout << bs(1, 1e6);
    return 0;
}