#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int MAX = 1000;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int wall[MAX][MAX];
bool visited[MAX][MAX];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, h, w, sr, sc, dr, dc;
    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> wall[i][j];
    cin >> h >> w >> sr >> sc >> dr >> dc;
    --sr, --sc, --dr, --dc;

    loop(i, row) loop(j, col) if (wall[i][j] == 1) {
        int r = max(0, i - h + 1), c = max(0, j - w + 1);
        for (int R = r; R <= i; ++R)
            for (int C = c; C <= j; ++C)
                wall[R][C] = -1;
    }
    
    visited[sr][sc] = true;
    queue<p> q;
    q.emplace(sr, sc), q.emplace(-1, -1);

    int ans = 0;
    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.emplace(-1, -1);
            continue;
        }
        if (r == dr && c == dc) break;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R + h > row || C < 0 || C + w > col || wall[R][C] || visited[R][C]) continue;
            visited[R][C] = true;
            q.emplace(R, C);
        }
    }
    cout << ans;
    return 0;
}