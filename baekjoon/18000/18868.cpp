#include <bits/stdc++.h>
using namespace std;

const int base = 1e4 + 7;
const int mod = 1e9 + 7;
const int mxN = 1e2;

int a[mxN], b[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    map<int, int> mp;
    int ans = 0;

    int M, N; cin >> M >> N;
    while (M--) {
        for (int i = 0; i < N; ++i)
            cin >> a[i];

        copy(a, a + N, b);
        sort(b, b + N);
        int K = unique(b, b + N) - b;

        long long h = 0;
        for (int i = 0; i < N; ++i)
            h = (h * base + lower_bound(b, b + K, a[i]) - b) % mod;
        ans += mp[h]++;
    }
    cout << ans;
    return 0;
}