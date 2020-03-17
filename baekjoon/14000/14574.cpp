#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;

bool v[max_N];
int c[max_N], p[max_N];
int rate[max_N];
int oppenent[max_N];

vector<int> battle[max_N];

void DFS(int u, int parent) {
    for (int i : battle[u]) if (i != parent) {
        DFS(i, u);
        cout << '\n' << u + 1 << ' ' << i + 1;
    }
}
inline int func(int a, int b) {
    return (c[a] + c[b]) / abs(p[a] - p[b]);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> p[i] >> c[i];

    v[0] = true;
    for (int i = 1; i < N; ++i)
        rate[i] = func(0, i);

    int cnt = N - 1;
    long long sum = 0;
    while (cnt--) {
        int k = 0;
        loop(i, N) if (!v[i] && rate[i] > rate[k])
            k = i;

        v[k] = true;
        sum += rate[k];
        battle[k].emplace_back(oppenent[k]);
        battle[oppenent[k]].emplace_back(k);

        loop(i, N) if (!v[i]) {
            int tmp = func(k, i);
            if (rate[i] < tmp) {
                rate[i] = tmp;
                oppenent[i] = k;
            }
        }
    }

    cout << sum;
    DFS(0, -1);
    return 0;
}