#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char board[5][5];
int N, ans_min = INT_MAX, ans_max = INT_MIN;
int mov[2][2] = { 1,0,0,1 };
void DFS(int r, int c, int res, char op)
{
    // 연산자 칸에 도착하면 op 바꿈
    if ((r + c) % 2) op = board[r][c];
    // 숫자칸에 도착하면 res 갱신
    else {
        int num = board[r][c] - '0';
        if (op == '+') res += num;
        else if (op == '-') res -= num;
        else res *= num;
    }
    
    if (r == N - 1 && c == N - 1) {
        ans_min = min(ans_min, res);
        ans_max = max(ans_max, res);
    }
    loop(i, 2) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R != N && C != N)
            DFS(R, C, res, op);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) loop(j, N) cin >> board[i][j];
    DFS(0, 0, 0, '+'); // 첫 칸은 무조건 더하기다.
    cout << ans_max << ' ' << ans_min;
    return 0;
}