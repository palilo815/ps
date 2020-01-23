#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int row, col, mov[4][2] = { -1,0,1,0,0,-1,0,1 };
char arr[400][400];

bool Candy(int r, int c)
{
    if (r > 0 && r < row - 1)
        if (arr[r - 1][c] == 'v' && arr[r + 1][c] == '^')
            return true;
    if (c > 0 && c < col - 1)
        if (arr[r][c - 1] == '>' && arr[r][c + 1] == '<')
            return true;
    return false;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    while (t--) {
        cin >> row >> col;
        loop(i, row) loop(j, col)
            cin >> arr[i][j];

        // 'o'를 기준으로 상하 or 좌우에 껍질이 있는지 확인
        int Ans = 0;
        loop(i, row) loop(j, col)
            if (arr[i][j] == 'o' && Candy(i, j))
                Ans++;
        cout << Ans << '\n';
    }
    return 0;
}