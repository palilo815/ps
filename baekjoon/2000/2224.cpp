#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool adj[52][52];
int ToNum(char c)
{
    if (c < 'a') return c - 'A';
    return c - 'a' + 26;
}
char ToChar(int n)
{
    if (n < 26) return 'A' + n;
    return 'a' + (n - 26);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    while (n-- > 0) {
        char u, v, x; cin >> u >> x >> x >> v;
        adj[ToNum(u)][ToNum(v)] = true;
    }

    // Floyd-Warshall
    loop(k, 52) loop(i, 52) loop(j, 52)
        adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
    int ans = 0;
    loop(i, 52) loop(j, 52) {
        if (i == j) continue;
        if (adj[i][j]) ++ans;
    }
    cout << ans << '\n';
    loop(i, 52)
        loop(j, 52) {
        if (i == j) continue;
        if (adj[i][j])
            cout << ToChar(i) << " => " << ToChar(j) << '\n';
    }
    return 0;
}