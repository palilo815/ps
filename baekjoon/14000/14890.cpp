#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 100;

int N, L;
int mat[max_N][max_N];
bool used[max_N][max_N];
bool slope(int r, int c, int dy, int dx) {
    int R = r + dy * L, C = c + dx * L;
    if (R < -1 || R > N || C < -1 || C > N) return false;
    if (dy) {
        for (int i = r;i != R;i += dy)
            if (used[i][c] || (mat[r][c] != mat[i][c])) return false;
        for (int i = r;i != R;i += dy)
            used[i][c] = true;
    }
    else {
        for (int j = c;j != C;j += dx)
            if (used[r][j] || (mat[r][c] != mat[r][j])) return false;
        for (int j = c;j != C;j += dx)
            used[r][j] = true;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N >> L;
    loop(i, N) loop(j, N) cin >> mat[i][j];
    int ans = 0;
    loop(i, N) loop(j, N - 1) {
        if (mat[i][j] + 1 == mat[i][j + 1]) {
            if (!slope(i, j, 0, -1)) break;
        }
        else if (mat[i][j] == mat[i][j + 1] + 1) {
            if (!slope(i, j + 1, 0, 1)) break;
        }
        else if (mat[i][j] != mat[i][j + 1]) break;
        if (j == N - 2) ++ans;
    }
    memset(used, 0, sizeof(used));
    loop(j, N) loop(i, N - 1) {
        if (mat[i][j] + 1 == mat[i + 1][j]) {
            if (!slope(i, j, -1, 0)) break;
        }
        else if (mat[i][j] == mat[i + 1][j] + 1) {
            if (!slope(i + 1, j, 1, 0)) break;
        }
        else if (mat[i][j] != mat[i + 1][j]) break;
        if (i == N - 2) ++ans;
    }
    cout << ans;
    return 0;
}