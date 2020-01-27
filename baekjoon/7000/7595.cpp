#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    while (1) {
        cin >> n;
        if (n == 0) break;
        for (int i = 1; i <= n; ++i)
            cout << string(i, '*') << '\n';
    }
    return 0;
}