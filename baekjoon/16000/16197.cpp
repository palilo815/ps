#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 20;

int row, col;
set<int> cache;
char board[max_N][max_N];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool is_out(int r, int c) {
    if (r < 0 || r >= row || c < 0 || c >= col) return true;
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int pos = 0; cin >> row >> col;
    loop(i, row) loop(j, col) {
        cin >> board[i][j];
        if (board[i][j] == 'o')
            pos = 10000 * pos + 100 * i + j;
    }

    // N범위가 작으므로 int 하나에 두 동전의 위치정보를 다 쑤셔박자
    queue<int> q;
    cache.insert(pos);
    q.push(pos), q.push(-1);
    int ans = 0;

    while (1) {
        int curr = q.front(); q.pop();
        if (curr == -1) {
            ++ans;
            if (q.empty() || ans > 10) {
                ans = -1; break;
            }
            q.push(curr); continue;
        }

        int y1 = curr / 1000000, x1 = (curr / 10000) % 100, y2 = (curr / 100) % 100, x2 = curr % 100;
        loop(i, 4) {
            // 한 칸씩 전진
            int Y1 = y1 + mov[i][0], Y2 = y2 + mov[i][0];
            int X1 = x1 + mov[i][1], X2 = x2 + mov[i][1];

            // 옮긴 동전이 떨어젔는지 확인
            // if 하나만 떨어졌다면 정답.
            // else if 둘 다 떨어지면 pass
            bool f1 = is_out(Y1, X1), f2 = is_out(Y2, X2);
            if (f1 ^ f2) {
                ++ans;
                if (ans > 10) ans = -1;
                goto OUT;
            }
            else if (f1 & f2) continue;

            // 벽을 만나면 막혀서 움직이지 못한다.
            if (board[Y1][X1] == '#') Y1 = y1, X1 = x1;
            if (board[Y2][X2] == '#') Y2 = y2, X2 = x2;

            // 다음에 움직일 좌표가 cache에 저장되지 않았다면 ㄱ
            int next_pos = Y1 * 1000000 + X1 * 10000 + Y2 * 100 + X2;
            if (cache.find(next_pos) == cache.end()) {
                cache.insert(next_pos);
                q.push(next_pos);
            }
        }
    }
OUT:;
    cout << ans;
    return 0;
}