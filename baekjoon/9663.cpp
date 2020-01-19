#include <iostream>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int n, board[15][15], ans;

// 내 공격범위의 칸을 num으로 칠한다.
void colour(int r, int c, int num)
{
    for (int i = r + 1; i < n; ++i)
        if (!board[i][c]) board[i][c] = num;
    for (int i = 1;r + i < n && c - i >= 0;++i)
        if (!board[r + i][c - i]) board[r + i][c - i] = num;
    for (int i = 1;r + i < n && c + i < n;++i)
        if (!board[r + i][c + i]) board[r + i][c + i] = num;
}

// board에서 num을 전부 지운다.
void erase(int r, int c, int num)
{
    for (int i = r + 1; i < n; ++i)
        if (board[i][c] == num) board[i][c] = 0;
    for (int i = 1;r + i < n && c - i >= 0;++i)
        if (board[r + i][c - i] == num) board[r + i][c - i] = 0;
    for (int i = 1;r + i < n && c + i < n;++i)
        if (board[r + i][c + i] == num) board[r + i][c + i] = 0;
}

// 퀸을 놓는다. 현재 놓여있는 퀸은 count개다.
void placing(int count)
{
    if (count == n) {
        ++ans;
        return;
    }
    loop(i, n)
        if (!board[count][i]) {
            colour(count, i, count + 1);
            placing(count + 1);
            erase(count, i, count + 1);
        }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    placing(0);
    cout << ans;
    return 0;
}