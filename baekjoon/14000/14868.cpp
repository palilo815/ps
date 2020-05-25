#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef pair<int, int> p;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int M = 2000;
const int max_K = 100001;

int parent[max_K];
int mat[M][M];

int _find(int u) {
    if (u < 0) u = -u;
    if (u == parent[u]) return u;
    return parent[u] = _find(parent[u]);
}
int _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (!u || !v || u == v) return 0;
    parent[u] = v;
    return 1;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    vector<p> vt1, vt2;
    vector<p>* q1 = &vt1, * q2 = &vt2;

    int N, K; cin >> N >> K;
    LOOP(i, K) parent[i] = i;
    LOOP(i, K) {
        int r, c; cin >> r >> c;
        mat[--r][--c] = i;
        q1->emplace_back(r, c);
    }

    int ans = 0;
    while (1) {
        for (auto [r, c] : *q1) {
            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (R < 0 || R >= N || C < 0 || C >= N) continue;
                K -= _union(mat[r][c], mat[R][C]);
            }
        }

        if (K == 1) break;
        ++ans;

        for (auto [r, c] : *q1) loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N || mat[R][C]) continue;
            mat[R][C] = mat[r][c];
            q2->emplace_back(R, C);
        }
        q1->clear();
        swap(q1, q2);
    }
    cout << ans;
    return 0;
}