#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char War[100][100];
int row, col, mov[4][2] = { -1,0,1,0,0,-1,0,1 };

// 뭉쳐있는 Team색 병사 수
// DFS 함수가 한 번 다녀가면 '\0'으로 바꿈
int DFS(int r, int c, char Team)
{
    int ret = 1;
    War[r][c] = 0;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col) continue;
        if (War[R][C] == Team)
            ret += DFS(R, C, Team);
    }
    return ret;
}
int main()
{
    cin.tie(NULL); cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    cin >> col >> row;
    loop(i, row) loop(j, col)
        cin >> War[i][j];
    int W = 0, B = 0, tmp;
    loop(i, row) loop(j, col) {
        if (War[i][j] == 'W') {
            tmp = DFS(i, j, 'W');
            W += tmp * tmp;
        }
        else if (War[i][j] == 'B') {
            tmp = DFS(i, j, 'B');
            B += tmp * tmp;
        }
    }
    cout << W << ' ' << B;
    return 0;
}