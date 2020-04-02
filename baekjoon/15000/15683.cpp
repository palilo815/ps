#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int MAX = 8;
const int mov[4][2] = { -1,0,0,1,1,0,0,-1 };

int row, col, ans;
int board[MAX][MAX];
vector<tup> cctv;
/*
1 : ->
2 : <- ->
3 : ^ ->
4 : <- ^ ->
5 : <- | ->
*/
bool is_out(int r, int c) {
    return r < 0 || r >= row || c < 0 || c >= col || board[r][c] == -1;
}
int safe_area() {
    int ret = 0;
    loop(i, row) loop(j, col)
        if (!board[i][j]) ++ret;
    return ret;
}
void check(int r, int c, int d, int val) {
    while (1) {
        r += mov[d][0], c += mov[d][1];
        if (is_out(r, c)) return;
        board[r][c] += val;
    }
}
void setting(int idx) {
    if (idx == cctv.size()) {
        ans = min(ans, safe_area());
        return;
    }

    auto [type, r, c] = cctv[idx];
    if (type == 1) loop(i, 4) {
        check(r, c, i, 1);
        setting(idx + 1);
        check(r, c, i, -1);
    }
    else if (type == 2) loop(i, 2) {
        check(r, c, i, 1);
        check(r, c, (i + 2) % 4, 1);
        setting(idx + 1);
        check(r, c, i, -1);
        check(r, c, (i + 2) % 4, -1);
    }
    else if (type == 3) loop(i, 4) {
        check(r, c, i, 1);
        check(r, c, (i + 1) % 4, 1);
        setting(idx + 1);
        check(r, c, i, -1);
        check(r, c, (i + 1) % 4, -1);
    }
    else loop(i, 4) {
        check(r, c, i, 1);
        check(r, c, (i + 1) % 4, 1);
        check(r, c, (i + 2) % 4, 1);
        setting(idx + 1);
        check(r, c, i, -1);
        check(r, c, (i + 1) % 4, -1);
        check(r, c, (i + 2) % 4, -1);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ans = INT_MAX;
    cin >> row >> col;
    vector<pair<int, int>> type_5;
    loop(i, row) loop(j, col) {
        cin >> board[i][j];
        if (board[i][j] == 6) board[i][j] = -1;
        else if (board[i][j] == 5) type_5.emplace_back(i, j);
        else if (0 < board[i][j] && board[i][j] < 5)
            cctv.emplace_back(board[i][j], i, j);
    }

    for (auto [r, c] : type_5) {
        for (int i = r - 1; i >= 0 && board[i][c] >= 0; --i)
            ++board[i][c];
        for (int i = r + 1; i < row && board[i][c] >= 0; ++i)
            ++board[i][c];
        for (int i = c - 1; i >= 0 && board[r][i] >= 0; --i)
            ++board[r][i];
        for (int i = c + 1; i < col && board[r][i] >= 0; ++i)
            ++board[r][i];
    }

    setting(0);
    cout << ans;
    return 0;
}