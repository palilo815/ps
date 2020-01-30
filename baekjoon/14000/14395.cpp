#include <bits/stdc++.h>
#define ll long long
using namespace std;

map<int, int> cache;
queue<int> q;
void go(int u, int v)
{
    if (cache.find(v) == cache.end()) {
        cache[v] = u;
        q.push(v);
    }
}
void trace(int E)
{
    stack<char> stk;
    while (1) {
        int parent = cache[E];
        if (parent == -1) break;
        if ((ll)parent * parent == E) stk.push('*');
        else if (parent * 2 == E) stk.push('+');
        else if (E == 0) stk.push('-');
        else stk.push('/');
        E = parent;
    }
    while (!stk.empty()) {
        cout << stk.top(); stk.pop();
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int S, E; cin >> S >> E;
    if (S == E) { cout << 0; return 0; }

    cache[S] = -1;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == E) {
            trace(E);
            return 0;
        }
        if ((ll)u * u <= E) go(u, u * u);
        if (u + u <= E) go(u, u + u);
        go(u, 0);
        go(u, 1);
    }
    cout << -1;
    return 0;
}