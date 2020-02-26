#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int MAX = 20;

int U, D, F, B, L, R;
const int mov[5][2] = { 0,0,0,1,0,-1,-1,0,1,0 };
int board[MAX][MAX];

void shift(int& a, int& b, int& c, int& d) {
    int tmp = d;
    d = c, c = b, b = a, a = tmp;
}
void solve(int y, int x, int d) {
    switch (d) {
    case 1: shift(U, R, D, L); break;
    case 2: shift(U, L, D, R); break;
    case 3: shift(U, B, D, F); break;
    case 4: shift(U, F, D, B);
    }
    if (board[y][x]) {
        D = board[y][x];
        board[y][x] = 0;
    }
    else board[y][x] = D;
    cout << U << '\n';
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, y, x, Q;
    cin >> row >> col >> y >> x >> Q;
    loop(i, row) loop(j, col)
        cin >> board[i][j];
    while (Q--) {
        int d; cin >> d;
        int Y = y + mov[d][0], X = x + mov[d][1];
        if (Y < 0 || Y >= row || X < 0 || X >= col) continue;
        solve(Y, X, d);
        y = Y, x = X;
    }
    return 0;
}