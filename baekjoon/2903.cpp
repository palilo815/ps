#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int n, x = 2;
    cin >> n;
    while (n--) x += x - 1;
    cout << x * x;
    return 0;
}