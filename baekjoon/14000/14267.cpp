#include <iostream>
#include <vector>
using namespace std;

const int max_N = 100000;

vector<int> adj[max_N + 1];
int lynch[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    int trash; cin >> trash;
    for (int v = 2; v <= N; ++v) {
        int u; cin >> u;
        adj[u].push_back(v);
    }
    while (M--) {
        int idx, val; cin >> idx >> val;
        lynch[idx] += val;
    }
    // i는 lynch[i]만큼 갈굼을 당했다.
    for (int i = 1; i <= N; ++i) {
        cout << lynch[i] << ' ';
        if (lynch[i]) for (int v : adj[i])
            lynch[v] += lynch[i];
    }
    return 0;
}