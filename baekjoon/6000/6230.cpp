#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1e4;

int hi[mx], lo[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> hi[i];
    loop(i, M) cin >> lo[i];

    sort(hi, hi + N, greater<int>());
    sort(lo, lo + M, greater<int>());

    int j = 0, ans = N;
    loop(i, N) {
        for (; j < M && lo[j] >= hi[i]; ++j) ;
        if (j ^ M) ++ans, ++j;
    }
    cout << ans;
    return 0;
}