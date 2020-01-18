#include <bits/stdc++.h> 
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int board[9][9];
bool used[10][10];

// (r,c)에 들어갈 수 있는 후보숫자 return
vector<int> hubo(int r, int c)
{
    vector<int> ret;
    vector<bool> check(10);
    loop(i, 9) {
        check[board[r][i]] = true;
        check[board[i][c]] = true;
    }
    int y = (r / 3) * 3, x = (c / 3) * 3;
    loop(i, 3) loop(j, 3)
        check[board[y + i][x + j]] = true;
    loop(i, 10)
        if (!check[i])
            ret.push_back(i);
    return ret;
}

// (r,c)가 빈칸인지 return
bool blank(int r, int c)
{
    if (r < 0 || r >= 9 || c < 0 || c >= 9) return false;
    return board[r][c] == 0;
}

bool solve(int pos)
{
    // pos부터 풀기 시작한다.
    for (int i = pos;i < 81;++i) {
        int r = i / 9, c = i % 9;
        // (r,c)가 비었으며, 가로 or 세로에 또 빈칸이 있을 경우
        if (!board[r][c] && (blank(r + 1, c) || blank(r, c + 1))) {
            // 자기 자리에 들어갈 숫자.
            vector<int> here = hubo(r, c);

            // 아래칸이 비었다면
            if (blank(r + 1, c)) {
                // 아래칸에 들어갈 후보숫자를 조사한 뒤,
                vector<int> ver = hubo(r + 1, c);

                // 도미노를 만들 수 있다면
                for (int a : here) for (int b : ver)
                    if (!used[a][b]) {
                        // 그 도미노로 칸을 채우고
                        used[a][b] = used[b][a] = true;
                        board[r][c] = a, board[r + 1][c] = b;

                        // 이 도미노를 썼을 때, 풀이가 성공하면 true
                        if (solve(pos + 1)) return true;
                        // 실패했다면 쓴 도미노 반납
                        used[a][b] = used[b][a] = false;
                    }
                // 모든 도미노를 다 넣어봐도 안된다면, 다시 칸 0으로 바꾼다.
                board[r][c] = board[r + 1][c] = 0;
            }
            
            // 위의 코드와 동일
            if (blank(r, c + 1)) {
                vector<int> hor = hubo(r, c + 1);
                for (int a : here) for (int b : hor)
                    if (!used[a][b]) {
                        used[a][b] = used[b][a] = true;
                        board[r][c] = a, board[r][c + 1] = b;
                        if (solve(pos + 1)) return true;
                        used[a][b] = used[b][a] = false;
                    }
                board[r][c] = board[r][c + 1] = 0;
            }

            // 모든 도미노가 실패하면, 이전에 잘못된 도미노를 넣었다.
            return false;
        }
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T = 0, N, a, b;
    string pos1, pos2;
    while (1) {
        cin >> N;
        if (N == 0) break;

        // initialize
        memset(board, 0, sizeof(board));
        memset(used, 0, sizeof(used));
        loop(i, 10) used[i][i] = true;

        // get input
        while (N--) {
            cin >> a >> pos1 >> b >> pos2;
            board[pos1[0] - 'A'][pos1[1] - '1'] = a;
            board[pos2[0] - 'A'][pos2[1] - '1'] = b;
            used[a][b] = used[b][a] = true;
        }
        for (int num = 1;num < 10;++num) {
            cin >> pos1;
            board[pos1[0] - 'A'][pos1[1] - '1'] = num;
        }

        // solve
        solve(0);

        // print answer
        cout << "Puzzle " << ++T << '\n';
        loop(i, 9) {
            loop(j, 9) cout << board[i][j];
            cout << '\n';
        }
    }
    return 0;
}