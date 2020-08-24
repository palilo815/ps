#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int mxN = 1e5;

p in[mxN], out[mxN];
bool check[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> in[i].first >> out[i].first;

    loop(i, N) in[i].second = i;
    loop(i, N) out[i].second = i;

    sort(in, in + N);
    sort(out, out + N);

    int ans = 0, cnt = 0;
    loop(i, N) {
        if (in[i].second == out[i].second) ans += cnt == 0;
        else {
            check[in[i].second] ? --cnt : (++cnt, check[in[i].second] = true);
            check[out[i].second] ? --cnt : (++cnt, check[out[i].second] = true);
        }
    }
    cout << ans;
    return 0;
}