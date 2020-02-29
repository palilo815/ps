#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mod = 1000007;
const int MAX = 50;

int board[MAX][MAX];
int DP[MAX][MAX][MAX + 1][MAX + 1]; // DP[r][c][cnt][last]

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, K; cin >> row >> col >> K;
    for (int i = 1; i <= K; ++i) {
        int r, c; cin >> r >> c;
        board[r - 1][c - 1] = i;
    }

    DP[0][0][board[0][0] != 0][board[0][0]] = 1;
    loop(r, row) loop(c, col) {
        if (r + 1 < row) {
            int nxt = board[r + 1][c];
            if (nxt) loop(cnt, K) loop(last, nxt) {
                DP[r + 1][c][cnt + 1][nxt] += DP[r][c][cnt][last];
                DP[r + 1][c][cnt + 1][nxt] %= mod;
            }
            else loop(cnt, K + 1) loop(last, K + 1) {
                DP[r + 1][c][cnt][last] += DP[r][c][cnt][last];
                DP[r + 1][c][cnt][last] %= mod;
            }
        }
        if (c + 1 < col) {
            int nxt = board[r][c + 1];
            if (nxt) loop(cnt, K) loop(last, nxt) {
                DP[r][c + 1][cnt + 1][nxt] += DP[r][c][cnt][last];
                DP[r][c + 1][cnt + 1][nxt] %= mod;
            }
            else loop(cnt, K + 1) loop(last, K + 1) {
                DP[r][c + 1][cnt][last] += DP[r][c][cnt][last];
                DP[r][c + 1][cnt][last] %= mod;
            }
        }
    }

    loop(i, K + 1) {
        int tmp = 0;
        loop(last, K + 1) tmp += DP[row - 1][col - 1][i][last];
        cout << tmp % mod << ' ';
    }
    return 0;
}