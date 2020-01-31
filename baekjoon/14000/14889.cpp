#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int n, arr[20][20];
bool TeamS[20];
int DFS(int prev, int team)
{
    TeamS[prev] = true;
    int ret;
    if (team == n / 2) {
        int Start = 0, Link = 0;
        loop(i, n) loop(j, n) {
            if (TeamS[i] && TeamS[j]) Start += arr[i][j];
            else if (!TeamS[i] && !TeamS[j]) Link += arr[i][j];
        }
        ret = abs(Start - Link);
    }
    else {
        ret = INT_MAX;
        for (int i = prev + 1; i < n; ++i)
            ret = min(ret, DFS(i, team + 1));
    }
    TeamS[prev] = false;
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    loop(i, n) loop(j, n) cin >> arr[i][j];
    int ans = INT_MAX;
    loop(i, n / 2)
        ans = min(ans, DFS(i, 1));
    cout << ans;
    return 0;
}