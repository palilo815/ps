#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;

int N;
string arr[max_N];
string rev[max_N];
int fenwick[max_N + 1];

void update(int i, int v) {
    for (++i; i <= N; i += i & -i)
        fenwick[i] += v;
}
int read(int i) {
    int ret = 0;
    for (++i; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> arr[i];
    loop(i, N) rev[i] = string(arr[i].rbegin(), arr[i].rend());

    sort(arr, arr + N);
    sort(rev, rev + N);

    loop(i, N) update(i, 1);
    long long ans = 0;
    loop(i, N) {
        string s = string(arr[i].rbegin(), arr[i].rend());
        int idx = lower_bound(rev, rev + N, s) - rev;
        ans += read(idx - 1);
        update(idx, -1);
    }
    cout << ans;
    return 0;
}