#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, M = 0, n = 0;
    while (1) {
        cin >> a >> b;
        if (b == 0) break;
        n += b - a;
        M = max(M, n);
    }
    cout << M;
    return 0;
}