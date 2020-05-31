#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;

int N;
p cow[max_N];
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
        cin >> cow[i].first,
        cow[i].second = i;
    sort(cow, cow + N, greater<p>());

    int ans = 0;
    loop(i, N) {
        int j = cow[i].second;
        int L = read(j - 1), R = read(N - 1) - read(j);
        if (L > R << 1 || R > L << 1) ++ans;
        update(j);
    }
    cout << ans;
    return 0;
}