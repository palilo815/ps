#include <bits/stdc++.h>
#define left (i<<1)
#define right (i<<1|1)
using namespace std;
using ll = long long;

const int mxN = 262144;

int tree[mxN];
ll subT[mxN], line[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> tree[i];

    // subT : ^
    // line : / or \

    for (int i = (N >> 1) + 1; i <= N; ++i)
        subT[i] = line[i] = tree[i];
    for (int i = N >> 1; i; --i) {
        subT[i] = max({subT[left], subT[right], tree[i] + line[left] + line[right]});
        line[i] = tree[i] + max(line[left], line[right]);
    }
    cout << max(subT[1], line[1]);

    int Q; cin >> Q;
    for (int u, w; Q; --Q) {
        cin >> u >> w;
        tree[u] = w;

        if (u > N >> 1) {
            line[u] = w, subT[u] = w;
            u >>= 1;
        }

        for (int i = u; i; i >>= 1) {
            subT[i] = max({subT[left], subT[right], tree[i] + line[left] + line[right]});
            line[i] = tree[i] + max(line[left], line[right]);
        }
        cout << '\n' << max(subT[1], line[1]);
    }
    return 0;
}