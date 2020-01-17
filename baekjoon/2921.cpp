#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int n, x = 0;
    cin >> n;
    loop(i, n + 1) loop(j, i + 1)
        x += i + j;
    cout << x;
    return 0;
}