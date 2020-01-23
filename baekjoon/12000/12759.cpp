#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int board[3][3];
bool win(int r, int c)
{
    int P = board[r][c];
    loop(i, 3) {
        if (board[i][c] != P) break;
        if (i == 2) return true;
    }
    loop(i, 3) {
        if (board[r][i] != P) break;
        if (i == 2) return true;
    }
    if (r == c)
        loop(i, 3) {
        if (board[i][i] != P) break;
        if (i == 2) return true;
    }
    if (r + c == 2)
        loop(i, 3) {
        if (board[i][2 - i] != P) break;
        if (i == 2) return true;
    }
    return false;
}
int winner()
{
    int P, r, c;
    cin >> P;
    loop(i, 9) {
        cin >> r >> c;
        --r, --c;
        board[r][c] = P;
        if (win(r, c)) return P;
        P = 3 - P;
    }
    return 0;
}
int main()
{
    cout << winner();
    return 0;
}