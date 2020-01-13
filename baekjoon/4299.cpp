#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b; cin >> a >> b;
    if (a - b < 0 || (a - b) % 2) cout << -1;
    else cout << (a - b) / 2 + b << ' ' << (a - b) / 2;
    return 0;
}