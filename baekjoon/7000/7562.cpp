#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
#define max_N 300
using namespace std;

bool board[max_N][max_N];
int mov[8][2] = { -1,-2,-2,-1,-2,1,-1,2,1,2,2,1,2,-1,1,-2 };
int main()
{
    int T; cin >> T;
    while (T--) {
        int N, sr, sc, er, ec;
        cin >> N >> sr >> sc >> er >> ec;
        memset(board, 0, sizeof(board));
        queue<P> q;
        q.push({ sr, sc }), q.push({ -1,-1 });
        int ans = 0;
        board[sr][sc] = true;
        while (1) {
            int r = q.front().first, c = q.front().second; q.pop();
            if (r == -1) {
                ++ans; q.push({ r,c });
                continue;
            }
            if (r == er && c == ec) break;
            loop(i, 8) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (R < 0 || R >= N || C < 0 || C >= N || board[R][C]) continue;
                q.push({ R,C });
                board[R][C] = true;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}