#include<bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int max_N = 10000;

int pay[max_N + 1];
vector<int> frnd[max_N + 1];
bool check[max_N + 1];

// id의 모든 친구를 check한다.
// 그리고 가장 적은 친구비를 return
int DFS(int id) {
    int ret = pay[id];
    check[id] = true;
    for (int x : frnd[id])
        if (!check[x])
            ret = min(ret, DFS(x));
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, money;
    cin >> N >> M >> money;
    LOOP(i, N) cin >> pay[i];
    while (M--) {
        int u, v; cin >> u >> v;
        frnd[u].push_back(v);
        frnd[v].push_back(u);
    }
    int sum = 0;
    LOOP(i, N)
        if (!check[i])
            sum += DFS(i);
    if (sum <= money) cout << sum;
    else cout << "Oh no";
    return 0;
}