#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool adj[501][501], selected[501];
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize **
    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }

    // 상근이의 친구를 골라서 my_friend에 넣는다.
    selected[1] = true;
    vector<int> my_friend;
    for (int i = 1;i <= N;++i)
        if (adj[1][i]) {
            selected[i] = true;
            my_friend.push_back(i);
        }
    int ans = my_friend.size();

    // 친구의 친구를 고른다.
    for (int x : my_friend)
        for (int i = 1;i <= N;++i)
            if (adj[x][i] && !selected[i]) {
                selected[i] = true;
                ++ans;
            }

    cout << ans;
    return 0;
}