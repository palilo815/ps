#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d < rhs.d;
    }
};

int a[mxN], nxt[mxN], when[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < k; ++i)
        cin >> a[i], --a[i];

    memset(when, 0x3f, sizeof(int) * k);
    for (int i = k - 1; ~i; --i) {
        nxt[i] = when[a[i]];
        when[a[i]] = i;
    }

    int* in = when;
    memset(in, 0, sizeof(int) * k);

    priority_queue<elem> pq;
    int ans = 0;
    for (int i = 0, cnt = 0; i < k; ++i) {
        if (in[a[i]]) {
            pq.emplace(nxt[i], a[i]);
            continue;
        }
        if (cnt == n) {
            int popped = pq.top().u;
            pq.pop();
            in[popped] = 0;
            --cnt, ++ans;
        }
        pq.emplace(nxt[i], a[i]);
        in[a[i]] = 1;
        ++cnt;
    }
    cout << ans;
}