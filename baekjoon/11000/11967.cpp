#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 100;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool visited[max_N][max_N];
bool light[max_N][max_N];
bool tmp[max_N][max_N];

vector<p> adj[max_N][max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int ux, uy, vx, vy;
        cin >> ux >> uy >> vx >> vy;
        adj[ux - 1][uy - 1].emplace_back(vx - 1, vy - 1);
    }

    queue<p> q;
    q.emplace(0, 0);
    visited[0][0] = light[0][0] = true;

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (auto [X, Y] : adj[x][y]) {
            light[X][Y] = true;
            if (!visited[X][Y] && tmp[X][Y]) {
                visited[X][Y] = true;
                q.emplace(X, Y);
            }
        }

        loop(i, 4) {
            int X = x + mov[i][0], Y = y + mov[i][1];
            if (X < 0 || X >= N || Y < 0 || Y >= N || visited[X][Y]) continue;
            if (light[X][Y]) {
                visited[X][Y] = true;
                q.emplace(X, Y);
            }
            else tmp[X][Y] = true;
        }
    }

    int ans = 0;
    loop(i, N) loop(j, N)
        if (light[i][j]) ++ans;
    cout << ans;
    return 0;
}