#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int MAX = 1000;
int castle[MAX][MAX];
bool visited[MAX][MAX];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    queue<p> q;
    loop(i, row) loop(j, col) {
        char x; cin >> x;
        if (x == '.') {
            q.push({ i,j });
            visited[i][j] = true;
        }
        else castle[i][j] = x - '0';
    }
    q.push({ -1,-1 });

    int ans = 0;
    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) break;
            ++ans; q.push({ -1,-1 });
            continue;
        }
        
        for (int R = r - 1; R <= r + 1; ++R) for (int C = c - 1; C <= c + 1; ++C) {
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C]) continue;
            if (castle[R][C]) --castle[R][C];
            if (!castle[R][C]) {
                q.push({ R,C });
                visited[R][C] = true;
            }
        }
    }
    cout << ans;
    return 0;
}