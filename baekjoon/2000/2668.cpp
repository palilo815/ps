#include <bits/stdc++.h>
using namespace std;

const int max_N = 100;
const int white = 0;
const int grey = -1;
const int black = 1;
const int cycle = 2;

int num[max_N + 1];
int colour[max_N + 1];

int DFS(int u) {
    if (colour[u] == grey) return u;
    else if (colour[u] == black || colour[u] == cycle) return 0;
    colour[u] = grey;
    int ret = DFS(num[u]);
    colour[u] = (ret ? cycle : black);
    if (ret == u) ret = 0;
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> num[i];
        if (i == num[i]) colour[i] = cycle;
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (!colour[i]) DFS(i);
        if (colour[i] == cycle) ++ans;
    }

    cout << ans;
    for (int i = 1; i <= N; ++i) if (colour[i] == cycle)
        cout << '\n' << i;
    return 0;
}