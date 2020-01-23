#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
char maze[50][50];
bool visited[50][50]; // 상남자는 int array따윈 쓰지 않는다.
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) loop(j, n) cin >> maze[i][j];
    deque<P> dq;
    dq.push_back({ 0,0 }), dq.push_back({ -1,-1 });

    int ans = 0;
    while (1) {
        int r = dq.front().first, c = dq.front().second; dq.pop_front();
        // pivot
        if (r == -1) {
            ++ans; dq.push_back({ r,c });
            continue;
        }
        // find answer
        if (r == n - 1 && c == n - 1) break;
        // move
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= n || C < 0 || C >= n || visited[R][C]) continue;

            if (maze[R][C] == '0')
                dq.push_back({ R,C });
            else
                dq.push_front({ R,C });
            visited[R][C] = true;
        }
    }
    cout << ans;
    return 0;
}