#include <bits/stdc++.h>
using namespace std;

struct candi {
    int s, q;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t w;
    cin >> n >> w;

    vector<candi> a(n);
    for (auto& [s, q] : a) cin >> s >> q;

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](auto& l, auto& r) {
        return a[l].s * a[r].q < a[r].s * a[l].q;
    });

    int ptr = 0, max_hire = 0;
    int64_t sum = 0, min_sum = 0;

    priority_queue<int> pq;

    for (const auto& i : idx) {
        const auto& [s, q] = a[i];
        sum += q;
        pq.emplace(q);

        while (sum * s > w * q) {
            sum -= pq.top();
            pq.pop();
        }

        if (pq.size() > max_hire || (pq.size() == max_hire && sum * s * a[idx[ptr]].q < min_sum * q * a[idx[ptr]].s))
            max_hire = pq.size(), min_sum = sum, ptr = &i - idx.data();
    }

    sort(idx.begin(), idx.begin() + ptr + 1, [&](auto& l, auto& r) {
        return a[l].q < a[r].q;
    });

    cout << max_hire << '\n';
    for (int i = 0; i < max_hire; ++i)
        cout << idx[i] + 1 << '\n';
}