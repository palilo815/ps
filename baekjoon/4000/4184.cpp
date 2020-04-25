#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int MAX = 1000;
const int current[8][2] = { -1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1 };

char ocean[MAX][MAX];
int dist[MAX][MAX];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> ocean[i][j];

    int T; cin >> T;
    while (T--) {
        int sr, sc, dr, dc; cin >> sr >> sc >> dr >> dc;
        --sr, --sc, --dr, --dc;
        loop(i, row) memset(&dist[i], 0x3f, sizeof(int) * col);
        dist[sr][sc] = 0;

        priority_queue<tup, vector<tup>, greater<tup>> pq;
        pq.emplace(0, sr, sc);

        while (1) {
            auto [d, r, c] = pq.top(); pq.pop();
            if (dist[r][c] < d) continue;
            if (r == dr && c == dc) break;

            loop(i, 8) {
                int R = r + current[i][0], C = c + current[i][1];
                if (R < 0 || R >= row || C < 0 || C >= col) continue;
                int D = (i == ocean[r][c] - '0') ? d : d + 1;

                if (dist[R][C] > D) {
                    dist[R][C] = D;
                    pq.emplace(D, R, C);
                }
            }
        }
        cout << dist[dr][dc] << '\n';
    }
    return 0;
}