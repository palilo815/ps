#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cache[21][21][21]; //A번째 벽장 열 차례, B와 C열려있음
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 21) loop(j, 21) loop(k, 21)
        cache[i][j][k] = INT32_MAX;
    int n, x, y, m;
    cin >> n >> x >> y;
    cache[0][min(x, y)][max(x, y)] = 0;
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        int Open; cin >> Open;
        // a 또는 b를 Open으로 바꿔야 한다.
        for (int a = 1; a < n; ++a)
            for (int b = 2; b <= n; ++b) {
                // a,b가 열려있는 경우가 없는 경우
                if (cache[i - 1][a][b] == INT32_MAX) continue;
                // 이미 열려있는 경우
                if (Open == a || Open == b) cache[i][a][b] = min(cache[i][a][b], cache[i - 1][a][b]);
                // 둘 중 하나를 Open을 만든다
                else {
                    if (Open < b) cache[i][Open][b] = min(cache[i][Open][b], cache[i - 1][a][b] + abs(a - Open));
                    if (Open > a) cache[i][a][Open] = min(cache[i][a][Open], cache[i - 1][a][b] + abs(Open - b));
                }
            }
    }
    int ans = INT32_MAX;
    loop(i, n + 1) loop(j, n + 1)
        ans = min(ans, cache[m][i][j]);
    cout << ans;
    return 0;
}