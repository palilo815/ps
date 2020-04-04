#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cache_N[10000];
char cache_C[10000];

inline int D(int n) { return (n * 2) % 10000; }
inline int S(int n) { return n ? n - 1 : 9999; }
inline int L(int n) {
    int msb = n / 1000;
    return (n - msb * 1000) * 10 + msb;
}
inline int R(int n) {
    int mlb = n % 10;
    return n / 10 + mlb * 1000;
}
void pushing(queue<int>& q, int u, int v, char order) {
    if (cache_C[v]) return;
    q.emplace(v);
    cache_C[v] = order;
    cache_N[v] = u;
}
void print_ans(int u, int v) {
    if (u == v) return;
    print_ans(u, cache_N[v]);
    cout << cache_C[v];
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) {
        memset(cache_C, 0, sizeof(cache_C));
        int src, dst; cin >> src >> dst;

        queue<int> q;
        q.emplace(src);
        cache_C[src] = '~';

        while (1) {
            int u = q.front(); q.pop();
            if (u == dst) break;
            pushing(q, u, D(u), 'D');
            pushing(q, u, S(u), 'S');
            pushing(q, u, L(u), 'L');
            pushing(q, u, R(u), 'R');
        }

        print_ans(src, dst);
        cout << '\n';
    }
    return 0;
}