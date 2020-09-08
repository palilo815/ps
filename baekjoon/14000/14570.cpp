#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;

int child[mxN + 1][2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> child[i][0] >> child[i][1];

    long long K; cin >> K;
    int u = 1;
    while (~child[u][0] || ~child[u][1]) {
        if (child[u][0] == -1) u = child[u][1];
        else if (child[u][1] == -1) u = child[u][0];
        else {
            u = child[u][1 - (K & 1)];
            K = (K + 1) >> 1;
        }
    }
    cout << u;
    return 0;
}