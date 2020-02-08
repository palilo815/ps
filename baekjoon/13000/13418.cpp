#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

int worst[max_N + 1], best[max_N + 1];
int find_rt(int u, int parent[])
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u], parent);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    loop(i, N + 1) worst[i] = best[i] = i;

    // edge_worst, edge_best
    int E_w = 0, E_b = 0;
    loop(i, M + 1) {
        int u, v, w; cin >> u >> v >> w;
        // 오르막 길이면 worst에 추가
        // 내리막이면 best에 추가
        int* parent = (w ? best : worst);
        u = find_rt(u, parent), v = find_rt(v, parent);
        if (u != v) {
            parent[u] = v;
            if (w) ++E_b;
            else ++E_w;
        }
    }

    // 만약 E_w == a이면
    // 최악의 경우라도 오르막 길은 a개밖에 못넣는다.
    // 따라서 worst 피로도 = a * a

    // 만약 E_b == b이면
    // 최고의 경우라도 내리막 길은 b개밖에 못넣는다.
    // 총 N개의 길을 지나야 하는데 나머지 N-b는 무조건 오르막 길이 되어야 한다.
    // 따라서 best 피로도 = (N-b) * (N-b)
    cout << E_w * E_w - (N - E_b) * (N - E_b);
    return 0;
}