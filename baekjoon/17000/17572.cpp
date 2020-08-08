#include <bits/stdc++.h>
using namespace std;
struct ball {
    int cnt, sz;
};

const int mx = 100;
const double pi = 3.14159265358979323846;

ball a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K, N; cin >> K >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].cnt >> a[i].sz;
    sort(a, a + N, [&](auto & a, auto & b) {
        return a.sz < b.sz;
    });

    K /= 2 * pi;
    int ans = 0;
    for (int i = 0; i < N ; ++i) {
        int x = min(a[i].cnt, K / a[i].sz);
        if (x) ans += x, K -= a[i].sz * x;
        else break;
    }
    cout << ans;
    return 0;
}