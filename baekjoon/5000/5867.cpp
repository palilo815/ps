#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 5e4;

string a[mxN], b[mxN];
int lo[mxN], hi[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i];
    copy(a, a + N, b);

    loop(i, N) sort(b[i].begin(), b[i].end(), greater<char>());
    sort(b, b + N);
    loop(i, N) {
        sort(a[i].begin(), a[i].end());
        lo[i] = lower_bound(b, b + N, a[i]) - b + 1;
    }

    loop(i, N) sort(b[i].begin(), b[i].end());
    sort(b, b + N);
    loop(i, N) {
        sort(a[i].begin(), a[i].end(), greater<char>());
        hi[i] = upper_bound(b, b + N, a[i]) - b;
    }

    loop(i, N) cout << lo[i] << ' ' << hi[i] << '\n';
    return 0;
}