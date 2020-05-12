#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int M = 20;

const int black = 1;
const int grey = -1;
const int white = 0;

int N;
char board[M][M];
int colour[M][M];
int ans[6], hubo[6];

void flood_it(int x, int y, int c, char num) {
    colour[x][y] = c;
    if (c == grey) ++hubo[num - '1'];

    loop(i, 4) {
        int X = x + mov[i][0], Y = y + mov[i][1];
        if (X < 0 || X >= N || Y < 0 || Y >= N || colour[X][Y]) continue;
        if (board[X][Y] == num) flood_it(X, Y, c, num);
        else if (c == black) flood_it(X, Y, grey, board[X][Y]);
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        cin >> N;
        loop(i, N) loop(j, N) cin >> board[i][j];

        memset(ans, 0, sizeof(ans));
        memset(hubo, 0, sizeof(hubo));
        memset(colour, 0, sizeof(colour));

        colour[0][0] = grey;
        ++hubo[board[0][0] - '1'];
        --ans[board[0][0] - '1'];

        while (any_of(hubo, hubo + 6, [](int i) {return i;})) {
            int target = max_element(hubo, hubo + 6) - hubo;
            hubo[target] = 0;
            ++ans[target];

            loop(x, N) loop(y, N)
                if (colour[x][y] == grey && board[x][y] == '1' + target)
                    flood_it(x, y, black, '1' + target);
        }

        cout << accumulate(ans, ans + 6, 0) << '\n';
        loop(i, 6) cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}