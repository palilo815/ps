#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxM = 3e5;

int N, M, a[mxM];

bool solve(int m) {
    int cnt = 0;
    loop(i, M) if ((cnt += (a[i] + m - 1) / m) > N)
        return false;
    return true;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    loop(i, M) cin >> a[i];

    int l = 1, r = 1e9;
    while (l ^ r) {
        int m = (l + r) >> 1;
        solve(m) ? (r = m) : (l = m + 1);
    }
    cout << l;
    return 0;
}