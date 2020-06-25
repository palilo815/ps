#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 100;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0 };

int N;
char colour[M][M];
bool visited[M][M];

void DFS(int r, int c) {
    visited[r][c] = true;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= N || C < 0 || C >= N || visited[R][C]) continue;
        if (colour[R][C] == colour[r][c])
            DFS(R, C);
    }
}
int solve() {
    int ret = 0;
    loop(i, N) loop(j, N) if (!visited[i][j]) {
        DFS(i, j);
        ++ret;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) loop(j, N) cin >> colour[i][j];
    cout << solve() << ' ';

    memset(visited, 0, sizeof(visited));
    loop(i, N) loop(j, N) if (colour[i][j] == 'G')
        colour[i][j] = 'R';
    cout << solve();
    return 0;
}