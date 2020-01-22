#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int board[9][9];
bool T[10];
bool check_row()
{
    loop(r, 9) {
        memset(T, 0, sizeof(T));
        loop(c, 9) {
            if (T[board[r][c]]) return false;
            T[board[r][c]] = true;
        }
    }
    return true;
}
bool check_col()
{
    loop(c, 9) {
        memset(T, 0, sizeof(T));
        loop(r, 9) {
            if (T[board[r][c]]) return false;
            T[board[r][c]] = true;
        }
    }
    return true;
}
bool check_box()
{
    loop(r, 3) loop(c, 3) {
        memset(T, 0, sizeof(T));
        int R = 3 * r, C = 3 * c;
        loop(i, 3) loop(j, 3) {
            if (T[board[R + i][C + j]]) return false;
            T[board[R + i][C + j]] = true;
        }
    }
    return true;
}
bool good_sudoku()
{
    if (check_row() && check_col() && check_box()) return true;
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        loop(i, 9) loop(j, 9) cin >> board[i][j];
        cout << "Case " << t << ": ";
        if (good_sudoku()) cout << "CORRECT\n";
        else cout << "INCORRECT\n";
    }
    return 0;
}