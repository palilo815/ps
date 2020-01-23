#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int n; cin >> n;
    loop(i, n)
        cout << string(i, ' ') << string(2 * n - 1 - 2 * i, '*') << '\n';
    for (int i = n - 2; i >= 0; --i)
        cout << string(i, ' ') << string(2 * n - 1 - 2 * i, '*') << '\n';
    return 0;
}