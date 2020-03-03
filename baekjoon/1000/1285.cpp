#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 20;

int N, ans;
bool coin[max_N][max_N];

void flip(int r) {
    if (r == N) {
        int cnt = 0;
        loop(j, N) {
            int tmp = 0;
            loop(i, N) if (coin[i][j]) ++tmp;
            cnt += min(tmp, N - tmp);
        }
        ans = min(ans, cnt);
        return;
    }
    flip(r + 1);
    loop(c, N) coin[r][c] = !coin[r][c];
    flip(r + 1);
    loop(c, N) coin[r][c] = !coin[r][c];
}

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ans = INT_MAX;
    cin >> N;
    loop(i, N) loop(j, N) {
        char x; cin >> x;
        if (x == 'H') coin[i][j] = true;
    }

    flip(0);
    cout << ans;
    return 0;
}