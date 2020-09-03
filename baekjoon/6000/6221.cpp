#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct hay {
    int w, b;
};

const int mxN = 20;

hay a[mxN];
int dp[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i].w >> a[i].b;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.w < b.w;
    });
    fill(dp, dp + N, 1);

    loop(i, N) {
        loop(j, i) if (a[j].b < a[i].b)
            dp[i] = max(dp[i], dp[j] + 1);
    }

    cout << *max_element(dp, dp + N);
    return 0;
}