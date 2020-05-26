#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> p;

const int max_N = 75000;

int M;
p arr[max_N];
int ord[max_N + 1];
int fenwick[max_N + 1];

void update(int i) {
    while (i <= M) {
        ++fenwick[i];
        i += i & -i;
    }
}
int read(int i) {
    int ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
bool cmp(const p& a, const p& b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first > b.first;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
start:;
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> arr[i].first >> arr[i].second;
        ord[i + 1] = arr[i].second;
    }

    sort(arr, arr + N, cmp);
    sort(ord + 1, ord + N + 1);
    M = unique(ord + 1, ord + N + 1) - ord;
    
    memset(fenwick + 1, 0, sizeof(int) * M);
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        int v = lower_bound(ord + 1, ord + M, arr[i].second) - ord;
        ans += read(v);
        update(v);
    }
    cout << ans << '\n';
    if (--T) goto start;
    return 0;
}