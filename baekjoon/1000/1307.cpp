#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 300;

int mat[mx][mx];

void odd(int br, int bc, int N, int num) {
    int r = br, c = bc + N / 2;
    for (int i = 1, R, C; i <= N * N; ++i, r = R, c = C) {
        mat[r][c] = i + num;
        R = r == br ? br + N - 1 : r - 1;
        C = c == bc + N - 1 ? bc : c + 1;
        if (mat[R][C]) R = r == br + N - 1 ? br : r + 1, C = c;
    }
}
void even(int N) {
    int h = N / 2;
    odd(0, 0, h, 0), odd(h, h, h, h * h), odd(0, h, h, h * h * 2), odd(h, 0, h, h * h * 3);

    loop(c, h / 2) loop(r, h) swap(mat[r][c], mat[r + h][c]);
    loop(c, h / 2 - 1) loop(r, h) swap(mat[r][N - 1 - c], mat[r + h][N - 1 - c]);
    swap(mat[h / 2][h / 2], mat[h + h / 2][h / 2]);
    swap(mat[h / 2][h / 2 - 1], mat[h + h / 2][h / 2 - 1]);
}
void _4th(int N) {
    int num = 0;
    loop(i, N) loop(j, N) {
        ++num;
        mat[i][j] = ((i & 3) == (j & 3) || ((i & 3) + (j & 3)) == 3) ? num : N * N + 1 - num;
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    if (N & 1) odd(0, 0, N, 0);
    else if (N & 3) even(N);
    else _4th(N);
    loop(i, N) {
        loop(j, N) cout << mat[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}