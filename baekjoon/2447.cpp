#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char Map[2188][2188];
void solve(int n, int x, int y)
{
    if (n == 1) {
        Map[x][y] = '*';
        return;
    }

    int div = n / 3;
    loop(i, 3) loop(j, 3) {
        if (i == 1 && j == 1) continue;
        solve(div, x + (div * i), y + (div * j));
    }
    return;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) loop(j, n) Map[i][j] = ' ';
    solve(n, 0, 0);
    loop(i, n) {
        loop(j, n) cout << Map[i][j];
        cout << '\n';
    }
    return 0;
}