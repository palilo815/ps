#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cache[10000];
inline int D(int n)
{
    return (n * 2) % 10000;
}
inline int S(int n)
{
    if (n != 0) return n - 1;
    return 9999;
}
inline int L(int n)
{
    int msb = n / 1000;
    return (n - msb * 1000) * 10 + msb;
}
inline int R(int n)
{
    int mlb = n % 10;
    return n / 10 + mlb * 1000;
}
void pushing(queue<int>& q, int n)
{
    int tmp;
    tmp = D(n);
    if (cache[tmp] == -1) {
        cache[tmp] = n;
        q.push(tmp);
    }
    tmp = S(n);
    if (cache[tmp] == -1) {
        cache[tmp] = n;
        q.push(tmp);
    }
    tmp = L(n);
    if (cache[tmp] == -1) {
        cache[tmp] = n;
        q.push(tmp);
    }
    tmp = R(n);
    if (cache[tmp] == -1) {
        cache[tmp] = n;
        q.push(tmp);
    }
}
void trace_back(int last)
{
    int curr = last, prev = cache[last];
    stack<char> stk;
    while (prev != -2) {
        if (D(prev) == curr) stk.push('D');
        else if (S(prev) == curr) stk.push('S');
        else if (L(prev) == curr) stk.push('L');
        else stk.push('R');
        curr = prev;
        prev = cache[prev];
    }
    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
    cout << '\n';
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, u, v;
    cin >> t;
    while (t--) {
        memset(cache, -1, sizeof(cache));
        cin >> u >> v;
        queue<int> q;
        q.push(u);
        cache[u] = -2;
        while (1) {
            int n = q.front(); q.pop();
            if (n == v) {
                trace_back(n);
                break;
            }
            pushing(q, n);
        }
    }
    return 0;
}