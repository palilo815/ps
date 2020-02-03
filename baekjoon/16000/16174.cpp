#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 64;

int board[max_N][max_N];
bool visited[max_N][max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> board[i][j];

    queue<P> q;
    q.push({ 0,0 });
    visited[0][0] = true;
    bool win = false;

    while (!q.empty()) {
        int r = q.front().first, c = q.front().second; q.pop();
        // 도착칸에는 -1이 써있다.
        if (board[r][c] == -1) { win = true; break; }

        // 칸에 써있는 숫자만큼 아래 or 오른쪽으로 점프한다.
        int R = r + board[r][c], C = c + board[r][c];
        if (R < N && !visited[R][c]) {
            q.push({ R,c });
            visited[R][c] = true;
        }
        if (C < N && !visited[r][C]) {
            q.push({ r,C });
            visited[r][C] = true;
        }
    }

    if (win) cout << "HaruHaru";
    else cout << "Hing";
    return 0;
}