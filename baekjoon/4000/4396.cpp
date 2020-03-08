#include <iostream>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int max_N = 10;

bool mine[max_N + 2][max_N + 2];
bool check[max_N + 2][max_N + 2];

bool touch_mine(int N) {
    LOOP(i, N) LOOP(j, N)
        if (check[i][j] && mine[i][j])
            return true;
    return false;
}
int count_mine(int r, int c) {
    int ret = 0;
    for (int i = r - 1; i <= r + 1; ++i)
        for (int j = c - 1; j <= c + 1; ++j)
            if (mine[i][j]) ++ret;
    return ret;
}
int main() {
    int N; cin >> N;
    char x;
    LOOP(i, N) LOOP(j, N) {
        cin >> x;
        if (x == '*') mine[i][j] = true;
    }
    LOOP(i, N) LOOP(j, N) {
        cin >> x;
        if (x == 'x') check[i][j] = true;
    }
    bool flag = touch_mine(N);

    LOOP(i, N) {
        LOOP(j, N) {
            if (check[i][j]) {
                if (mine[i][j]) cout << '*';
                else cout << count_mine(i, j);
            }
            else {
                if (mine[i][j] && flag) cout << '*';
                else cout << '.';
            }
        }
        cout << '\n';
    }
    return 0;
}