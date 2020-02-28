#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int max_N = 200;
const int max_K = 1000;

int board[max_N][max_N];
vector<p> vir[max_K + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    loop(i, N) loop(j, N) {
        cin >> board[i][j];
        if (board[i][j]) vir[board[i][j]].push_back({ i,j });
    }

    queue<p> q;
    loop(i, K + 1) for (p pos : vir[i])
        q.push(pos);
    q.push({ -1,-1 });

    int S, Y, X; cin >> S >> Y >> X;
    int T = 0;
    while (T < S) {
        auto [r, c] = q.front(); q.pop();

        if (r == -1) {
            ++T; q.push({ -1,-1 });
            continue;
        }

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N || board[R][C]) continue;
            board[R][C] = board[r][c];
            q.push({ R,C });
        }
    }
    cout << board[Y - 1][X - 1];
    return 0;
}