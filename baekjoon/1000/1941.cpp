#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

// matrix : 'Y','S'로 이루어진 표
char mat[5][5];
// check_stdt : 고른 7명의 위치 표시
// check_DFS : DFS용 임시 array
bool check_stdt[5][5], check_DFS[5][5];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int DFS(int r, int c) {
    int ret = 1;
    check_DFS[r][c] = false;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R == -1 || R == 5 || C == -1 || C == 5 || !check_DFS[R][C]) continue;
        ret += DFS(R, C);
    }
    return ret;
}
// pos부터 고르기 시작, 현재 고른 학생은 각가 Y,S명
int solve(int Y, int S, int pos)
{
    if (Y >= 4) return 0;
    if (Y + S == 7) {
        memcpy(check_DFS, check_stdt, 25);
        return (DFS(pos / 5, pos % 5) == 7);
    }

    int ret = 0;
    for (int i = pos + 1; i < 19 + Y + S; ++i) {
        check_stdt[i / 5][i % 5] = true;
        if (mat[i / 5][i % 5] == 'Y')
            ret += solve(Y + 1, S, i);
        else
            ret += solve(Y, S + 1, i);
        check_stdt[i / 5][i % 5] = false;
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 5) loop(j, 5) cin >> mat[i][j];
    cout << solve(0, 0, -1);
    return 0;
}