#include <bits/stdc++.h>
using namespace std;

const int mx = 1e5;

int a[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    priority_queue<int> con;
    int N, M; cin >> N >> M;
    while (N--) {
        int w; cin >> w;
        con.emplace(w);
    }

    for (int i = 0; i < M; ++i)
        cin >> a[i];
    sort(a, a + M);

    int l = 0, r = M;
    while (l ^ r) {
        auto pq = con;
        int m = (l + r) >> 1;
        bool over = false;
        for (int i = m; ~i; --i) {
            int w = pq.top(); pq.pop();
            if (w < a[i]) {over = true; break;}
            pq.emplace(w - a[i]);
        }

        over ? (r = m) : (l = m + 1);
    }
    cout << l;
    return 0;
}