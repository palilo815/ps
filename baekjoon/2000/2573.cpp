#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int row, col;
int ice[300][300], sink[300][300];
bool visited[300][300];

void AfterYear()
{
    // 해당 칸의 sink만큼 ice 감소
    // 올해에 다 녹게 된 ice는 음수로 만든다.
    loop(r, row) loop(c, col)
        if (ice[r][c] > 0) {
            ice[r][c] -= sink[r][c];
            if (ice[r][c] == 0) --ice[r][c];
        }

    // ice < 0 : 올해에 다 녹은 얼음
    // ice == 0 : 이전에 녹은 얼음
    loop(r, row) loop(c, col)
        // 빙산이 하나 없어졌으므로 주변 칸의 sink도 1씩 증가해야 한다.
        if (ice[r][c] < 0) {
            ice[r][c] = 0;
            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                ++sink[R][C];
            }
        }
}

void DFS(int r, int c)
{
    visited[r][c] = true;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (ice[R][C] > 0 && !visited[R][C])
            DFS(R, C);
    }
}

bool OnePiece()
{
    memset(visited, 0, sizeof(visited));
    // 빙산 한 조각 발견
    loop(i, row) loop(j, col)
        if (ice[i][j] > 0) {
            DFS(i, j);
            goto OUT;
        }
    // 전부 녹았다.
    return false;
OUT:;
    // 만약 방문 안한 새로운 빙산조각을 발견한다면,
    // 빙산이 분리되었단 뜻이다.
    loop(i, row) loop(j, col)
        if (ice[i][j] > 0 && !visited[i][j])
            return false;
    // 아직 분리되지 않았다.
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> ice[i][j];
    for (int r = 1; r < row - 1; ++r)
        for (int c = 1; c < col - 1; ++c)
            loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (ice[R][C] == 0)++sink[r][c];
        }

    int ans = 0;
    do {
        AfterYear();
        ++ans;
    } while (OnePiece());

    loop(i, row) loop(j, col)
        if (ice[i][j] > 0) {
            cout << ans;
            goto RET;
        }
    cout << 0;
RET:;
    return 0;
}