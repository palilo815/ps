#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 1001;

int* parent;
int worst[mxN], best[mxN];

int _find(int u) {
    return ~parent[u] ? (parent[u] = _find(parent[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    memset(worst, -1, sizeof(int) * (N + 1));
    memset(best, -1, sizeof(int) * (N + 1));

    // edge_worst, edge_best
    int e_w = 0, e_b = 0;
    loop(i, M + 1) {
        int u, v, w; cin >> u >> v >> w;
        // 오르막 길이면 worst에 추가
        // 내리막이면 best에 추가
        parent = w ? best : worst;
        u = _find(u), v = _find(v);
        if (u ^ v) {
            parent[u] = v;
            w ? ++e_b : ++e_w;
        }
    }

    // 만약 e_w == a이면
    // 최악의 경우라도 오르막 길은 a개밖에 못넣는다.
    // 따라서 worst 피로도 = a * a

    // 만약 e_b == b이면
    // 최고의 경우라도 내리막 길은 b개밖에 못넣는다.
    // 총 N개의 길을 지나야 하는데 나머지 N-b는 무조건 오르막 길이 되어야 한다.
    // 따라서 best 피로도 = (N-b) * (N-b)
    cout << e_w * e_w - (N - e_b) * (N - e_b);
    return 0;
}