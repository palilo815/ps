#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a[2][5];
    loop(i, 5) cin >> a[0][i];
    loop(i, 5) cin >> a[1][i];
    bool f = true;
    loop(i, 5)
        if (!(a[0][i] ^ a[1][i])) f = false;
    if (f) cout << 'Y';
    else cout << 'N';
    return 0;
}