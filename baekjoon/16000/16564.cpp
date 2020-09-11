#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1e6;

int N, K, a[mxN];

bool valid(int m) {
    int cnt = 0;
    loop(i, N) if (a[i] < m && (cnt += m - a[i]) > K)
        return false;
    return true;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> K;
    loop(i, N) cin >> a[i];

    int l = 1, r = 1e9;
    while (l ^ r) {
        int m = (l + r + 1) >> 1;
        valid(m) ? (l = m) : (r = m - 1);
    }
    cout << l;
    return 0;
}