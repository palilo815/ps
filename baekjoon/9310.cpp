#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll n, d[2], r[2], Num[3];
    while (cin >> n) {
        if (n == 0) break;
        loop(i, 3) cin >> Num[i];
        loop(i, 2) {
            d[i] = Num[i + 1] - Num[i];
            r[i] = Num[i + 1] / Num[i];
        }
        ll Ans;
        if (d[0] == d[1]) Ans = n * (2 * Num[0] + (n - 1) * d[0]) / 2;
        else Ans = Num[0] * (pow(r[0], n) - 1) / (r[0] - 1);
        cout << Ans << '\n';
    }
    return 0;
}