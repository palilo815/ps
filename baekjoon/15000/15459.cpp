#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

const int mxN = 1e5;

int N, f[mxN], s[mxN], num[mxN];
ll K;

bool solve(int k) {
    ll sum = 0;
    loop(i, N) {
        if (s[i] > k) sum = 0;
        else if ((sum += f[i]) >= K) return true;
    }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> K;
    loop(i, N) cin >> f[i] >> s[i];

    copy(s, s + N, num);
    sort(num, num + N);
    int M = unique(num, num + N) - num;

    int l = 0, r = M;
    while (l ^ r) {
        int m = (l + r) >> 1;
        solve(num[m]) ? (r = m) : (l = m + 1);
    }
    cout << num[l];
    return 0;
}