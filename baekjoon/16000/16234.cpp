#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 50;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int arr[max_N][max_N];
int parent[max_N * max_N], p[max_N * max_N], cnt[max_N * max_N];

int _find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u == v) return;
    parent[u] = v;
    p[v] += p[u];
    cnt[v] += cnt[u];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, L, R; cin >> N >> L >> R;
    loop(i, N) loop(j, N) cin >> arr[i][j];
    
    int ans = 0;
    while (1) {
        loop(i, N * N) {
            parent[i] = i;
            p[i] = arr[i / N][i % N];
            cnt[i] = 1;
        }
        bool finished = true;
        loop(i, N) loop(j, N) loop(k, 4) {
            int r = i + mov[k][0], c = j + mov[k][1];
            if (r < 0 || r >= N || c < 0 || c >= N) continue;
            int gap = abs(arr[i][j] - arr[r][c]);
            if (gap >= L && gap <= R) {
                finished = false;
                _union(i * N + j, r * N + c);
            }
        }
        if (finished) break;
        loop(i, N * N) {
            int rt = _find(i);
            arr[i / N][i % N] = p[rt] / cnt[rt];
        }
        ++ans;
    }
    cout << ans;
    return 0;
}