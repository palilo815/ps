#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

vector<p> pos;

int solve(int len) {
    int ret = 0;
    auto x = pos.begin();
    while (x != pos.end()) {
        ++ret;
        x = lower_bound(x, pos.end(), make_pair(x->first + len, 0));
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int R, C, K, N;
    cin >> R >> C >> K >> N;

    pos.resize(N);
    for (auto& [c, r] : pos)
        cin >> r >> c;
    sort(pos.begin(), pos.end());

    int l = 0, r = 2000000;
    for (auto [c, r] : pos)
        l = max(l, r);

    int ans;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (solve(m) <= K) {
            ans = m;
            r = m - 1;
        }
        else l = m + 1;
    }
    cout << ans;
    return 0;
}