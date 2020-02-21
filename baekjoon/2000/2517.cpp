#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 500000;

int N;
p arr[max_N];
int ans[max_N];
int fenwick[max_N + 1];

void update(int idx) {
    while (idx <= N) {
        ++fenwick[idx];
        idx += (idx & -idx);
    }
}
int read(int idx) {
    int ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) {
        int x; cin >> x;
        arr[i] = { x,i + 1 };
    }
    sort(arr, arr + N, greater<p>());
    loop(i, N) {
        int idx = arr[i].second;
        ans[idx - 1] = read(idx) + 1;
        update(idx);
    }
    loop(i, N) cout << ans[i] << '\n';
    return 0;
}