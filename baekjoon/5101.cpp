#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, d, s;
    while (cin >> a >> d >> s) {
        if (d == 0) break;
        int gap = s - a;
        if (gap % d == 0) cout << gap / d + 1 << '\n';
        else cout << "X\n";
    }
    return 0;
}