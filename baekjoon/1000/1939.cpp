#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

vector<P> bridge[100001];

// vertex의 개수는 V개, 중량은 load
// u->v로 이동하는게 가능한가?
bool BFS(int u, int v, int V, int load) {
    queue<int> q;
    vector<bool> visited(V + 1);
    q.push(u);
    while (!q.empty()) {
        int curr = q.front();q.pop();
        if (curr == v) return true;
        for (P p : bridge[curr]) {
            int to = p.first, w = p.second;
            if (!visited[to] && w >= load) {
                visited[to] = true;
                q.push(to);
            }
        }
    }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, L = 0, R = 0, ans = -1;
    cin >> V >> E;
    while (E--) {
        int u, v, w; cin >> u >> v >> w;
        R = max(R, w);
        bridge[u].push_back(make_pair(v, w));
        bridge[v].push_back(make_pair(u, w));
    }
    int from, to;
    cin >> from >> to;

    // binary-search
    while (L <= R) {
        int mid = L + (R - L) / 2;
        if (BFS(from, to, V, mid)) {
            ans = mid;
            L = mid + 1;
        }
        else
            R = mid - 1;
    }
    cout << ans;
    return 0;
}