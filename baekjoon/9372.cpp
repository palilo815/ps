#include<bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n, m, u, v;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        while (m--)
            cin >> u >> v;
        cout << n - 1 << '\n';
    }
    return 0;
}