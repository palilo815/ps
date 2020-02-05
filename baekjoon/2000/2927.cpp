// 못 풀었다
// segment tree 복습하고 다시 풀자
// 경로상의 펭귄 숫자 합만 구하면 된다
#include <bits/stdc++.h>
using namespace std;
const int max_N = 30000;

int parent[max_N + 1];
int penguin[max_N + 1];
int total[max_N + 1];
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
bool union_tr(int u, int v)
{
    u = find_rt(u), v = find_rt(v);
    if (u == v) return false;
    parent[u] = v;
    total[v] += total[u];
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> penguin[i];
        total[i] = penguin[i];
        parent[i] = i;
    }

    int Q; cin >> Q;
    while (Q--) {
        string q;
        int a, b, delta;
        cin >> q >> a >> b;
        switch (q[0]) {
        case 'b':
            if (union_tr(a, b)) cout << "yes";
            else cout << "no";
            break;
        case 'p':
            delta = b - penguin[a];
            penguin[a] = b;
            total[find_rt(a)] += delta;
            break;
        case 'e':
            a = find_rt(a), b = find_rt(b);
            if (a == b) cout << total[a];
            else cout << "impossible";
        }
        cout << '\n';
    }
    return 0;
}