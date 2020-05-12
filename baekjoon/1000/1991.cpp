#include <iostream>
using namespace std;

int child[26][2];

void solve(int u, int order) {
    if (u == -1) return;
    if (order == 0) cout << (char)(u + 'A');
    solve(child[u][0], order);
    if (order == 1) cout << (char)(u + 'A');
    solve(child[u][1], order);
    if (order == 2) cout << (char)(u + 'A');
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    while (N--) {
        char p, l, r; cin >> p >> l >> r;
        child[p - 'A'][0] = (l == '.' ? -1 : l - 'A');
        child[p - 'A'][1] = (r == '.' ? -1 : r - 'A');
    }
    for (int i = 0; i < 3; ++i) {
        solve(0, i);
        cout << '\n';
    }
    return 0;
}