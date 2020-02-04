#include<bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int E = 100;

int mov[E + 1];
bool visited[E + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    LOOP(i, 100) mov[i] = i;
    int N, M; cin >> N >> M;
    N += M;
    while (N--) {
        int u, v; cin >> u >> v;
        mov[u] = v;
    }

    queue<int> q;
    q.push(1), q.push(-1);
    int ans = 0;
    while (1) {
        int curr = q.front(); q.pop();
        if (curr == -1) {
            q.push(curr), ++ans;
            continue;
        }
        if (curr == 100) break;
        LOOP(i, 6) {
            int Next = mov[curr + i];
            if (!visited[Next]) {
                q.push(Next);
                visited[Next] = true;
            }
        }
    }
    cout << ans;
    return 0;
}