#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1080;

int N, ans, x[mxN], y[mxN], r[mxN];
bool visited[mxN];

void dfs(int u) {
    ans = u;
    visited[u] = true;
    loop(v, N) if (!visited[v]) {
        int dx = x[u] - x[v], dy = y[u] - y[v], sr = r[u] + r[v];
        if (dx * dx + dy * dy == sr * sr) {
            dfs(v);
            break;
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) cin >> x[i] >> y[i] >> r[i];
    loop(i, N) if (x[i] == 0 && y[i] == 0) {
        swap(x[0], x[i]), swap(y[0], y[i]), swap(r[0], r[i]);
        break;
    }

    dfs(0);

    cout << x[ans] << ' ' << y[ans];
    return 0;
}