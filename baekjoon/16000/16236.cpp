#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;

int board[20][20], N, mov[4][2] = { -1,0,0,-1,0,1,1,0 };
bool visited[20][20];

// 가장 가까운 물고기를 먹고, 그 거리를 return
int BFS(int& row, int& col, int shark)
{
    memset(visited, 0, sizeof(visited));
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0, 20 * row + col });
    while (!pq.empty()) {
        int d = pq.top().first;
        int r = pq.top().second / 20, c = pq.top().second % 20;
        pq.pop();

        // 현재 칸에 물고기가 있고, 그 크기가 상어보다 작다면
        // 잡아먹는다.
        if (board[r][c] && board[r][c] < shark) {
            board[r][c] = 0;
            row = r, col = c;
            return d;
        }
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R == -1 || R == N || C == -1 || C == N) continue;

            // 자기보다 큰 물고기가 있는 곳은 가지 못한다.
            if (board[R][C] <= shark && !visited[R][C]) {
                visited[R][C] = true;
                pq.push({ d + 1, 20 * R + C });
            }
        }
    }
    return -1;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int shark = 2, eat = 0, r, c, ans = 0;
    cin >> N;
    loop(i, N) loop(j, N) {
        cin >> board[i][j];
        if (board[i][j] == 9) {
            board[i][j] = 0;
            r = i, c = j;
        }
    }
    // r, c = 시작 좌표

    while (1) {
        // 만약 물고기가 없다면 BFS는 -1을 return
        int dist = BFS(r, c, shark);
        if (dist == -1) break;
        ans += dist;

        // 물고기를 자기 크기만큼 먹으면 크기가 커진다.
        ++eat;
        if (eat == shark) {
            ++shark;
            eat = 0;
        }
    }
    cout << ans;
    return 0;
}