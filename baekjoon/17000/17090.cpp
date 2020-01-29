#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 500;

// 어차피 DP값은 0, 1, 2니까 char로도 충분
// 소중한 메모리 아끼쟈
char maze[max_N][max_N], DP[max_N][max_N];
bool visited[max_N][max_N];
int row, col;
int solve(int r, int c)
{
    // 바깥으로 나갔다면 탈출 성공
    if (r < 0 || r >= row || c < 0 || c >= col) return 1;
    char& ret = DP[r][c];
    if (ret) return ret;

    // 왔던 곳을 또 왔다면 빙빙 도는거다.
    if (visited[r][c]) return 2;

    visited[r][c] = true;
    switch (maze[r][c]) {
    case 'U':
        return ret = solve(r - 1, c);
    case 'R':
        return ret = solve(r, c + 1);
    case 'D':
        return ret = solve(r + 1, c);
    case 'L':
        return ret = solve(r, c - 1);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> maze[i][j];
    int ans = 0;
    loop(i, row) loop(j, col)
        if (solve(i, j) == 1)
            ++ans;
    cout << ans;
    return 0;
}