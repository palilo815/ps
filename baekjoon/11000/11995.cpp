#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

const int mxN = 2000;

int a[mxN + 2], b[mxN + 2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int A, B, N, M;
    cin >> A >> B >> N >> M;

    loop(i, N) cin >> a[i];
    loop(i, M) cin >> b[i];

    sort(a, a + N);
    sort(b, b + M);
    a[N++] = A, b[M++] = B;

    adjacent_difference(a, a + N, a);
    adjacent_difference(b, b + M, b);

    sort(a, a + N);
    sort(b, b + M);
    a[N] = b[M] = INT_MAX;

    ll ans = (ll)a[0] * (M - 1) + (ll)b[0] * (N - 1);
    for (int i = 1, j = 1, cnt = N + M - 3; cnt; --cnt) {
        if (a[i] < b[j])
            ans += (ll)a[i++] * (M - j);
        else
            ans += (ll)b[j++] * (N - i);
    }
    cout << ans;
    return 0;
}