#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;

bool board[10][9], visited[10][9];
int mov[4][2] = { -1,0,0,1,1,0,0,-1 };

bool is_out(int r, int c)
{
    return (r < 0 || r >= 10 || c < 0 || c >= 9);
}
void go(queue<P>& q, int r, int c, int d1, int d2)
{
    int dr = mov[d1][0], dc = mov[d1][1];

    int R = r + dr, C = c + dc;
    if (is_out(R, C) || board[R][C]) return;

    if (dr) dc = dr * d2;
    else dr = dc * d2;

    R += dr, C += dc;
    if (is_out(R, C) || board[R][C]) return;
    R += dr, C += dc;
    if (is_out(R, C)) return;

    visited[R][C] = true;
    q.push({ R,C });
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int src_r, src_c, dst_r, dst_c;
    cin >> src_r >> src_c >> dst_r >> dst_c;

    board[dst_r][dst_c] = true;
    queue<P> q;
    visited[src_r][src_c] = true;
    q.push({ src_r,src_c }); q.push({ -1,-1 });
    int ans = 0;

    while (1) {
        int r = q.front().first, c = q.front().second; q.pop();

        if (r == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.push({ -1,-1 });
            continue;
        }
        if (r == dst_r && c == dst_c) break;

        loop(i, 4) {
            go(q, r, c, i, -1);
            go(q, r, c, i, 1);
        }
    }
    cout << ans;
    return 0;
}