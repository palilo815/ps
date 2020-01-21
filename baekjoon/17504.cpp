#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;

// 분자, 분모
ll arr[15][2];
ll Euclid(ll a, ll b) {
    if (a == 0) return b;
    return Euclid(b % a, a);
}
// a + 1/b
void PLUS(ll* a, ll* b) {
    swap(b[0], b[1]);
    a[0] *= b[1];
    a[1] = b[1];
    a[0] += b[0];
    ll gcd = Euclid(a[0], a[1]);
    a[0] /= gcd, a[1] /= gcd;
}
int main()
{
    int N; cin >> N;
    loop(i, N) {
        cin >> arr[i][0];
        arr[i][1] = 1;
    }
    for (int i = N - 2;i >= 0;--i)
        PLUS(arr[i], arr[i + 1]);
    cout << arr[0][0] - arr[0][1] << ' ' << arr[0][0];
    return 0;
}