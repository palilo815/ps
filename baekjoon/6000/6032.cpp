#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;
struct toy {
    int joy, price, i;
};

const int mx = 25000;

toy a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i].joy >> a[i].price;
    loop(i, N) a[i].i = i + 1;

    sort(a, a + N, [&](toy & a, toy & b) {
        return (ll)a.joy * b.price > (ll)b.joy * a.price;
    });

    cout << a[0].price + a[1].price + a[2].price;
    loop(i, 3) cout << '\n' << a[i].i;
    return 0;
}