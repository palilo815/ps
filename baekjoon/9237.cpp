#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int Tree[100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, ans = 0;
    cin >> n;
    loop(i, n) cin >> Tree[i];
    sort(Tree, Tree + n, greater<int>());
    loop(i, n)
        ans = max(ans, i + 2 + Tree[i]);
    cout << ans;
    return 0;
}