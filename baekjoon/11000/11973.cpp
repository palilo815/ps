#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 5e4;

int N, K, a[mxN + 1];

bool solve(int m) {
    auto it = a;
    loop(i, K) it = upper_bound(it, a + N, *it + m * 2);
    return it == a + N;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> K;
    loop(i, N) cin >> a[i];
    sort(a, a + N);

    int l = 0, r = 5e8 + 1;
    while (l ^ r) {
        int m = (l + r) / 2;
        solve(m) ? (r = m) : (l = m + 1);
    }
    cout << l;
    return 0;
}