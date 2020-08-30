#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

const int mxN = 1e6;

int N, a[mxN];
ll M;

bool enough(ll m) {
    ll cnt = 0;
    loop(i, N) if ((cnt += m / a[i]) >= M)
        return true;
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    loop(i, N) cin >> a[i];

    ll lo = 1, hi = 1e12;
    while (lo ^ hi) {
        ll m = (lo + hi) >> 1;
        enough(m) ? (hi = m) : (lo = m + 1);
    }
    cout << lo;
    return 0;
}