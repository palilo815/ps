#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int x = 1 << 9;
const int max_N = 500;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int N;
char board[max_N][max_N];
int dist[max_N][max_N][2];
int warp[max_N][max_N][4];

inline bool in_range(int r, int c) {
    return (0 <= r && r < N && 0 <= c && c < N);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, dr, dc; cin >> N >> T >> dr >> dc;
    loop(i, N) loop(j, N) cin >> board[i][j];
    --dr, --dc;

    // initialize "warp" array
    // if warp[r][c][i] == d:
    //     (r,c) * mov[i] * d = (R,C)
    //     board[R][C] == '#'
    loop(i, N) loop(j, N) if (board[i][j] == '#') {
        loop(k, 4) {
            int r = i, c = j, cnt = 0;
            do {
                r += mov[k][0], c += mov[k][1], ++cnt;
                if (!in_range(r, c)) break;
                warp[r][c][3 - k] = cnt;
            } while (board[r][c] != '#');
        }
    }

    fill(&dist[0][0][1], &dist[N][0][0], INT_MAX);

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 0);

    // Dijkstra
    while (1) {
        auto [d, mode] = pq.top(); pq.pop();
        int c = mode % x; mode /= x;
        int r = mode % x; mode /= x;
        if (r == dr && c == dc) break;

        if (mode) {
            if (dist[r][c][0] > d) {
                dist[r][c][0] = d;
                pq.emplace(d, r * x + c);
            }
            loop(i, 4) if (warp[r][c][i]) {
                int R = r + mov[i][0] * warp[r][c][i];
                int C = c + mov[i][1] * warp[r][c][i];
                if (dist[R][C][1] > d + 1) {
                    dist[R][C][1] = d + 1;
                    pq.emplace(d + 1, x * x + R * x + C);
                }
            }
        }
        else {
            if (dist[r][c][1] > d + T) {
                dist[r][c][1] = d + T;
                pq.emplace(d + T, x * x + r * x + c);
            }
            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (in_range(R, C) && dist[R][C][0] > d + 1) {
                    dist[R][C][0] = d + 1;
                    pq.emplace(d + 1, R * x + C);
                }
            }
        }
    }
    cout << min(dist[dr][dc][0], dist[dr][dc][1]);
    return 0;
}