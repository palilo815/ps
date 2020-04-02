#include <iostream>
#include <cstring>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef long long ll;

const int MAX = 200;

char board[MAX + 2][MAX + 2];
ll DP[2][MAX + 1][MAX + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, L; cin >> row >> col >> L;
    LOOP(i, row) LOOP(j, col) cin >> board[i][j];

    string s; cin >> s;
    char prv = s[L - 1];
    LOOP(i, row) LOOP(j, col) if (board[i][j] == prv)
        DP[0][i][j] = 1;

    int src = 0, dst = 1;
    for (int i = L - 2; i >= 0; --i) {
        memset(DP[dst], 0, sizeof(DP[dst]));
        char cur = s[i];
        LOOP(i, row) LOOP(j, col) if (board[i][j] == cur)
            for (int a = i - 1; a <= i + 1; ++a)
                for (int b = j - 1; b <= j + 1; ++b)
                    if (!(a == i && b == j) && board[a][b] == prv)
                        DP[dst][i][j] += DP[src][a][b];
        src = 1 - src, dst = 1 - dst, prv = cur;
    }

    ll ans = 0;
    LOOP(i, row) LOOP(j, col)
        ans += DP[src][i][j];
    cout << ans;
    return 0;
}