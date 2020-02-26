#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int max_N = 50;
const int max_M = 10;

int N;
int arr[max_N][max_N];
int dist[max_M][max_N][max_N];
int ans[max_N][max_N];

void BFS(p src, int idx) {
    queue<p> q;
    q.push(src);
    dist[idx][src.first][src.second] = 0;
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N || arr[R][C] == 1 || dist[idx][R][C] != -1) continue;
            dist[idx][R][C] = dist[idx][r][c] + 1;
            q.push({ R,C });
        }
    }
}
int calc_T() {
    int ret = 0;
    loop(i, N) loop(j, N) if (arr[i][j] != 1) {
        if (ans[i][j] == -1) return INT_MAX;
        ret = max(ret, ans[i][j]);
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int M;
    vector<p> hubo;
    cin >> N >> M;
    loop(i, N) loop(j, N) {
        cin >> arr[i][j];
        if (arr[i][j] == 2) hubo.push_back({ i,j });
    }

    memset(dist, -1, sizeof(dist));
    int vir = hubo.size();
    loop(i, vir)
        BFS(hubo[i], i);

    vector<bool> select(vir);
    fill(select.begin(), select.begin() + M, true);
    int min_T = INT_MAX;

    do {
        memset(ans, -1, sizeof(ans));
        loop(k, vir) if (select[k]) {
            loop(i, N) loop(j, N) {
                if (dist[k][i][j] == -1) continue;
                ans[i][j] = (ans[i][j] == -1 ? dist[k][i][j] : min(ans[i][j], dist[k][i][j]));
            }
        }
        min_T = min(min_T, calc_T());
    } while (prev_permutation(select.begin(), select.end()));
    cout << (min_T == INT_MAX ? -1 : min_T);
    return 0;
}