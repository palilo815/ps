#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char board[8][8];
int mov[4][2] = { 0,1,1,-1,1,0,1,1 };

bool valid(int r, int c)
{
    loop(i, 4) {
        int R = r, C = c;
        int dr = mov[i][0], dc = mov[i][1];
        while (1) {
            R += dr, C += dc;
            if (R == 8 || C == -1 || C == 8) break;
            if (board[R][C] == '*') return false;
        }
    }
    return true;
}
int main()
{
    // ** initialize **
    int cnt = 0;
    loop(i, 8) loop(j, 8) {
        cin >> board[i][j];
        if (board[i][j] == '*') ++cnt;
    }
    
    // 퀸이 8개가 아니라면
    if (cnt != 8) {
        cout << "invalid";
        return 0;
    }

    // 어떤 퀸이 다른 퀸을 잡을 수 있다면
    loop(i, 8) loop(j, 8)
        if (board[i][j] == '*') {
            if (!valid(i, j)) {
                cout << "invalid";
                return 0;
            }
            break;
        }

    cout << "valid";
    return 0;
}