#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 100;
const int bar = 1 << 7;
const int mov[6][3] = { -1,0,0, 0,-1,0, 0,0,-1, 0,0,1, 0,1,0, 1,0,0 };

int box[MAX][MAX][MAX];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int height, row, col;
    cin >> col >> row >> height;

    queue<int> q;
    loop(h, height) loop(r, row) loop(c, col) {
        cin >> box[h][r][c];
        if (box[h][r][c] == 1)
            q.emplace(h * bar * bar + r * bar + c);
    }
    q.emplace(-1);

    int ans = 0;
    while (1) {
        int h = q.front(); q.pop();
        if (h == -1) {
            if (q.empty()) break;
            ++ans; q.emplace(-1);
            continue;
        }

        int c = h % bar; h /= bar;
        int r = h % bar; h /= bar;

        loop(i, 6) {
            int H = h + mov[i][0], R = r + mov[i][1], C = c + mov[i][2];
            if (H < 0 || H >= height || R < 0 || R >= row || C < 0 || C >= col || box[H][R][C]) continue;
            q.emplace(H * bar * bar + R * bar + C);
            box[H][R][C] = 1;
        }
    }
    loop(h, height) loop(r, row) loop(c, col)
        if (!box[h][r][c]) {
            cout << -1;
            return 0;
        }
    cout << ans;
    return 0;
}