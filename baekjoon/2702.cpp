#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int a, b; cin >> a >> b;
        int MOD = gcd(a, b);
        cout << a * b / MOD << ' ' << MOD << '\n';
    }
    return 0;
}