#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 500000;

int N;
p arr[max_N];
int fenwick[max_N + 1];

void update(int i) {
    for (++i; i <= N; i += i & -i)
        ++fenwick[i];
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
    loop(i, N)
        cin >> arr[i].first,
        arr[i].second = i;
    sort(arr, arr + N, greater<p>());

    long long ans = 0;
    loop(i, N) {
        int idx = arr[i].second;
        ans += read(idx - 1);
        update(idx);
    }
    cout << ans;
    return 0;
}