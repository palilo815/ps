#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int gcd(int m, int n)
{
    if (m == 0) return n;
    return gcd(n % m, m);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, a[100];
    cin >> n;
    loop(i, n) cin >> a[i];
    for (int i = 1; i < n; ++i) {
        int mod = gcd(a[0], a[i]);
        cout << a[0] / mod << '/' << a[i] / mod << '\n';
    }
    return 0;
}