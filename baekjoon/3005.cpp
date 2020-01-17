#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<bool,bool>

int row, col;
char puzzle[20][20];
P start_p(int r, int c)
{
    P ret = make_pair(0, 0);
    // 가로로 시작되는 단어인가?
    if (r - 1 == -1 || puzzle[r - 1][c] == '#')
        if (r + 1 != row && puzzle[r + 1][c] != '#')
            ret.first = true;
    // 세로로 시작되는 단어인가?
    if (c - 1 == -1 || puzzle[r][c - 1] == '#')
        if (c + 1 != col && puzzle[r][c + 1] != '#')
            ret.second = true;
    return ret;
}
string get_s(int r, int c, int direction)
{
    string ret = "";
    if (direction) // 가로
        for (int i = r; i < row; ++i) {
            if (puzzle[i][c] == '#') break;
            ret += puzzle[i][c];
        }
    else // 세로
        for (int j = c; j < col; ++j) {
            if (puzzle[r][j] == '#') break;
            ret += puzzle[r][j];
        }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> puzzle[i][j];
    string tmp, ans = "~"; //ASCII 126
    loop(i, row) loop(j, col) {
        if (puzzle[i][j] != '#') {
            P p = start_p(i, j);
            if (p.first) {
                tmp = get_s(i, j, 1);
                if (tmp < ans) ans = tmp;
            }
            if (p.second) {
                tmp = get_s(i, j, 0);
                if (tmp < ans) ans = tmp;
            }
        }
    }
    cout << ans;
    return 0;
}