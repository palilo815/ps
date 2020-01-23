#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    for (int i = 1; i < n;++i)
        cout << string(n - i, ' ') << string(i, '*') << '\n';
    for (int i = n; i >= 0;--i)
        cout << string(n - i, ' ') << string(i, '*') << '\n';
    return 0;
}