#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int n, MAP[500][500], Cache[500][500];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int TopDown(int r, int c)
{
    int& ret = Cache[r][c];
    if (ret) return ret;
    ret = 1;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R == n || C < 0 || C == n || MAP[R][C] <= MAP[r][c]) continue;
        ret = max(ret, TopDown(R, C) + 1);
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    loop(i, n) loop(j, n) cin >> MAP[i][j];

    int ans = 0;
    loop(i, n) loop(j, n)
        ans = max(ans, TopDown(i, j));
    cout << ans;
    return 0;
}