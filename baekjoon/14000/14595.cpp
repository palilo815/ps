#include <iostream>
using namespace std;
const int max_N = 1000000;

int parent[max_N + 1];
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        parent[i] = i;

    // parent[i] : i방의 오른쪽 끝 index
    while (M--) {
        int x, y; cin >> x >> y;
        x = find_rt(x), y = find_rt(y);
        while (x < y) {
            parent[x] = y;
            x = find_rt(x + 1);
        }
    }

    int ans = 0, idx = 1;
    while (idx <= N) {
        ++ans;
        idx = find_rt(idx) + 1;
    }
    cout << ans;
    return 0;
}