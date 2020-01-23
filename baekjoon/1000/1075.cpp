#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, f;
    cin >> n >> f;
    n = n / 100 * 100;
    while (n % f) ++n;

    n %= 100;
    if (n >= 10) cout << n;
    else cout << 0 << n;
    return 0;
}