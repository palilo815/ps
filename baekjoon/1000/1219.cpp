#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

const int max_N = 100;
const int max_M = 100;

int edge[max_M][3];
int earn[max_N];
ll money[max_N];
bool path[max_N][max_N];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, src, dst;
    cin >> N >> src >> dst >> M;
    loop(i, M) loop(j, 3) cin >> edge[i][j];
    loop(i, N) cin >> earn[i];

    loop(i, N) money[i] = INT64_MIN;
    money[src] = earn[src];

    // Floyd-Warshall 로 u에서 v로 도달 가능한지 구해놓는다.
    loop(i, N) path[i][i] = true;
    loop(i, M) path[edge[i][0]][edge[i][1]] = true;
    loop(k, N) loop(i, N) loop(j, N)
        path[i][j] = path[i][j] || (path[i][k] && path[k][j]);

    // N번 반복한다.
    // N번 시도에서 update가 되고, 해당 지점에서 dst까지의 경로가 있다면
    // neg_cycle을 이용해서 dst에 도착이 가능하단 뜻이다.
    bool update = false;
    bool neg_cycle = false;
    int cnt = N;
    while (cnt--) {
        update = false;
        loop(i, M) {
            int u = edge[i][0], v = edge[i][1], w = edge[i][2];
            if (money[u] != INT64_MIN && money[v] < money[u] + earn[v] - w) {
                if (cnt == 0 && path[v][dst]) neg_cycle = true;
                money[v] = money[u] + earn[v] - w;
                update = true;
            }
        }
        if (!update) break;
    }

    if (money[dst] == INT64_MIN) cout << "gg";
    else if (neg_cycle) cout << "Gee";
    else cout << money[dst];
    return 0;
}