#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
int V;
vector<int> adj[10001];
int visited[10001]; // 어떤 컴퓨터가 다녀갔는지

int DFS(int start, int Index)
{
    visited[start] = Index;
    int ret = 1, len = adj[start].size();

    loop(i, len) {
        int Next = adj[start][i];
        // Index computer가 안다녀갔으면 DFS 전진
        if (visited[Next] != Index)
            ret += DFS(Next, Index);
    }
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int E;
    cin >> V >> E;
    while (E-- > 0) {
        int v, u;
        cin >> v >> u;
        adj[u].push_back(v);
    }
    int Ans = 0;	 // 해킹할 수 있는 최댓값
    vector<int> AnsV;// 여기에 정답인 컴퓨터를 넣는다.
    for (int i = 1; i <= V; ++i) {
        // tmp : i번 컴퓨터로 해킹할 수 있는 개수
        int tmp = DFS(i, i);

        if (tmp == Ans)
            AnsV.push_back(i);
        else if (tmp > Ans) {
            Ans = tmp;
            AnsV.clear();
            AnsV.push_back(i);
        }
    }
    sort(AnsV.begin(), AnsV.end());
    for (int numV : AnsV)
        cout << numV << ' ';
    return 0;
}