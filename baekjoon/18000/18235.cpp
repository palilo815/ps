#include <bits/stdc++.h>
using namespace std;

const int max_N = 500000;

int visited[2][max_N + 1];

int main() {
    int N, A, B; cin >> N >> A >> B;
    visited[0][A] = 1, visited[1][B] = 1;

    queue<int> q;
    q.push(A), q.push(-1), q.push(B), q.push(-1);

    int ans = 0, ori = 0;
    while (ans < 19) {
        int u = q.front(); q.pop();
        if (u == -1) {
            if (ori == 1) ++ans;
            ori = 1 - ori;
            q.push(-1);
            continue;
        }

        if (visited[1 - ori][u] == ans + 1) break;

        int v;
        v = u - pow(2, ans);
        if (v > 0 && visited[ori][v] != ans + 2) {
            visited[ori][v] = ans + 2;
            q.push(v);
        }
        v = u + pow(2, ans);
        if (v <= N && visited[ori][v] != ans + 2) {
            visited[ori][v] = ans + 2;
            q.push(v);
        }
    }
    cout << (ans == 19 ? -1 : ans);
    return 0;
}