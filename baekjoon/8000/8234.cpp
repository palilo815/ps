#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct elem {
    int i, val;
    elem(int i, int val) : i(i), val(val) {}
    bool operator<(const elem& rhs) const {
        return val < rhs.val;
    }
};

const int mxN = 25e4;

int a[mxN], b[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    for (int i = 0; i < N; ++i)
        cin >> a[i];
    for (int i = 0; i < N; ++i)
        cin >> b[i];

    priority_queue<elem> pq;
    ll sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += a[i];
        if (sum < b[i]) {
            if (!pq.empty() && pq.top().val > b[i]) {
                sum += pq.top().val - b[i];
                pq.pop();
                pq.emplace(i, b[i]);
            }
        } else {
            sum -= b[i];
            pq.emplace(i, b[i]);
        }
    }

    int sz = pq.size();
    vector<int> ans(sz);

    for (int i = 0; i < sz; ++i) {
        ans[i] = pq.top().i;
        pq.pop();
    }

    sort(ans.begin(), ans.end());
    cout << sz << '\n';
    for (int& x : ans) cout << x + 1 << ' ';
}