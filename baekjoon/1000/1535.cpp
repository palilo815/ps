#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int n, hp[20], happy[20], cache[20][101];
int TopDown(int x, int y)
{
    if (x == n) return 0;
    int& ret = cache[x][y];
    if (ret) return ret;
    if (y - hp[x] > 0) ret = TopDown(x + 1, y - hp[x]) + happy[x];
    ret = max(ret, TopDown(x + 1, y));
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    loop(i, n) cin >> hp[i];
    loop(i, n) cin >> happy[i];
    cout << TopDown(0, 100);
    return 0;
}