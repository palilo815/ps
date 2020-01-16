#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int n; cin >> n;
    for (int i = 1;i < n;++i)
        cout << string(i, '*') << string(2 * (n - i), ' ') << string(i, '*') << '\n';
    for (int i = n; i > 0;--i)
        cout << string(i, '*') << string(2 * (n - i), ' ') << string(i, '*') << '\n';
    return 0;
}