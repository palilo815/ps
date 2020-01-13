#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int row, col;
char Floor[100][100];

// 이어지는 바닥장식을 다 '\0'으로 바꿔버린다.
void ceiling(int r, int c, char T)
{
    if (T == '-') {
        for (int i = 1;c + i < col;++i) {
            if (Floor[r][c + i] == '-')
                Floor[r][c + i] = 0;
            else break;
        }
        for (int i = -1;c + i >= 0;--i) {
            if (Floor[r][c + i] == '-')
                Floor[r][c + i] = 0;
            else break;
        }
    }
    else {
        for (int i = 1;r + i < row;++i) {
            if (Floor[r + i][c] == '|')
                Floor[r + i][c] = 0;
            else break;
        }
        for (int i = -1;r + i >= 0;--i) {
            if (Floor[r + i][c] == '|')
                Floor[r + i][c] = 0;
            else break;
        }
    }
    Floor[r][c] = 0;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int ans = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> Floor[i][j];
    loop(i, row) loop(j, col)
        if (Floor[i][j]) {
            ceiling(i, j, Floor[i][j]);
            ++ans;
        }
    cout << ans;
    return 0;
}