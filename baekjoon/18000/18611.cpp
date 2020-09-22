#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct elem {
    int x, i;
    elem(int x, int i) : x(x), i(i) {}
    bool operator<(const elem& rhs) const {
        return x > rhs.x;
    }
};

const int mxN = 1e5;

char ans[mxN << 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    N += M;

    priority_queue<elem> pq;
    ll sum = 0;
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        sum += x;
        if (x > 0) ans[i] = 'r';
        else {
            pq.emplace(x, i);
            while (sum < 0) {
                ans[pq.top().i] = 'd';
                sum -= pq.top().x;
                pq.pop();
            }
        }
    }

    for (int i = 0; i < N; ++i)
        switch (ans[i]) {
        case 'r':
            cout << "resupplied\n";
            break;
        case 'd':
            cout << "declined\n";
            break;
        default:
            cout << "approved\n";
        }
    return 0;
}