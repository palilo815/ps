#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 100;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int N;
int mat[max_N][max_N];
int dist[max_N][max_N];
queue<p> q;

void DFS(int r, int c, int num) {
    mat[r][c] = num;
    q.emplace(r, c);
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= N || C < 0 || C >= N || mat[R][C] != -1)
            continue;
        DFS(R, C, num);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    loop(i, N) loop(j, N) {
        int x; cin >> x;
        mat[i][j] = -x;
    }
    
    int cnt = 0;
    loop(i, N) loop(j, N) if (mat[i][j] == -1)
        DFS(i, j, ++cnt);

    int ans = INT_MAX;
    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) break;
        int nara = mat[r][c];

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N) continue;
            if (!mat[R][C]) {
                mat[R][C] = nara;
                q.emplace(R, C);
                dist[R][C] = dist[r][c] + 1;
            }
            else if (mat[R][C] != nara) {
                ans = min(ans, dist[r][c] + dist[R][C]);
                q.emplace(-1, -1);
            }
        }
    }
    cout << ans;
    return 0;
}