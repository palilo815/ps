#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { 1,0,0,1,-1,0,0,-1 };
const int max_N = 20;

queue<int> q;
bool wall[max_N][max_N];
bool visited[max_N][max_N][max_N][max_N][4];

void _push(int r1, int c1, int r2, int c2, int d) {
    if (visited[r1][c1][r2][c2][d]) return;
    visited[r1][c1][r2][c2][d] = true;
    q.push(d * 32 * 32 * 32 * 32 + r1 * 32 * 32 * 32 + c1 * 32 * 32 + r2 * 32 + c2);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = N - 1; i >= 0; --i) loop(j, N) {
        char x; cin >> x;
        if (x == 'H') wall[i][j] = true;
    }
    int ans = 0;
    visited[0][0][0][0][0] = true;
    q.push(0), q.push(-1);
    while (1) {
        int d = q.front(); q.pop();
        if (d == -1) {
            if (q.empty()) { cout << "error\n"; return 0; }
            ++ans; q.push(-1);
            continue;
        }

        int r1, c1, r2, c2;
        c2 = d % 32; d /= 32;
        r2 = d % 32; d /= 32;
        c1 = d % 32; d /= 32;
        r1 = d % 32; d /= 32;
        if (r1 == N - 1 && c1 == N - 1 && r2 == N - 1 && c2 == N - 1) break;

        _push(r1, c1, r2, c2, (d + 1) % 4);
        _push(r1, c1, r2, c2, (d + 3) % 4);

        int R1, C1, R2, C2;
        if (r1 == N - 1 && c1 == N - 1) R1 = r1, C1 = c1;
        else R1 = r1 + mov[d][0], C1 = c1 + mov[d][1]; 
        if (r2 == N - 1 && c2 == N - 1) R2 = r2, C2 = c2;
        else R2 = r2 + mov[(d + 1) % 4][0], C2 = c2 + mov[(d + 1) % 4][1];

        if (R1 < 0 || R1 >= N || C1 < 0 || C1 >= N || wall[R1][C1]) R1 = r1, C1 = c1;
        if (R2 < 0 || R2 >= N || C2 < 0 || C2 >= N || wall[R2][C2]) R2 = r2, C2 = c2;
        _push(R1, C1, R2, C2, d);
    }
    cout << ans;
    return 0;
}