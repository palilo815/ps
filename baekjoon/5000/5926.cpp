#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct cow {
    int pos, id;
};

const int mxN = 5e4;

cow a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i].pos >> a[i].id;

    unordered_map<int, int> cnt;
    loop(i, N) cnt[a[i].id] = 1;
    int total = cnt.size();

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.pos < b.pos;
    });

    deque<cow> dq;
    dq.emplace_back(a[0]);
    cnt[a[0].id] = 2;

    int ans = INT_MAX;;
    for (int i = 1, s = 1; i < N; ++i) {
        s += cnt[a[i].id]++ == 1;
        dq.emplace_back(a[i]);

        while (cnt[dq.front().id] ^ 2) {
            --cnt[dq.front().id];
            dq.pop_front();
        }

        if (s == total)
            ans = min(ans, dq.back().pos - dq.front().pos);
    }
    cout << ans;
    return 0;
}