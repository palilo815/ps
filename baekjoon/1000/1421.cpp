#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_N = 1000;

int wood[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, C, W; cin >> N >> C >> W;
    loop(i, N) cin >> wood[i];

    ll ans = 0;
    for (int h = 1; h <= 10000; ++h) {
        ll sum = 0;
        loop(i, N) if(wood[i] >= h) {
            ll tmp = (wood[i] % h ? -C : 0);
            tmp += wood[i] / h * h * W;
            tmp -= (wood[i] / h - 1) * C;
            if (tmp > 0) sum += tmp;
        }
        ans = max(sum, ans);
    }
    cout << ans;
    return 0;
}