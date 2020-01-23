#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0; i<n; ++i)

int height[100][100];
bool sink[100][100], visited[100][100];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

void DFS(int r, int c, int N)
{
    visited[r][c] = true;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= N || C < 0 || C >= N || visited[R][C] || sink[R][C]) continue;
        DFS(R, C, N);
    }
}

int cnt_safe(int N)
{
    int ret = 0;
    loop(i, N) loop(j, N)
        if (!sink[i][j] && !visited[i][j]) {
            ++ret;
            DFS(i, j, N);
        }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> height[i][j];

    int ans = 1;
    for (int rain = 1; rain < 101; ++rain) {
        bool updated = false;
        loop(i, N) loop(j, N) {
            if (height[i][j] == rain) {
                updated = true;
                sink[i][j] = true;
            }
        }
        if (updated) {
            memset(visited, 0, sizeof(visited));
            ans = max(ans, cnt_safe(N));
        }
    }
    cout << ans;
    return 0;
}