#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct tank {
    int r, c, id;
};

const int mxN = 5e2;

tank a[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i].r >> a[i].c;
    loop(i, N) --a[i].r, --a[i].c, a[i].id = i + 1;

    vector<int> v1;
    vector<char> v2;
    vector<pair<int, int>> up_q, dw_q;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.r < b.r;
    });
    loop(i, N) {
        auto& [r, c, id] = a[i];
        if (r > i) up_q.emplace_back(i, r - i);
        if (r < i) dw_q.emplace_back(i, i - r);
    }

    sort(up_q.begin(), up_q.end(), [&](auto & x, auto & y) {
        return a[x.first].r < a[y.first].r;
    });
    for (auto& [i, cnt] : up_q) {
        v1.insert(v1.end(), cnt, a[i].id);
        v2.insert(v2.end(), cnt, 'U');
    }
    sort(dw_q.begin(), dw_q.end(), [&](auto & x, auto & y) {
        return a[x.first].r > a[y.first].r;
    });
    for (auto& [i, cnt] : dw_q) {
        v1.insert(v1.end(), cnt, a[i].id);
        v2.insert(v2.end(), cnt, 'D');
    }

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.c < b.c;
    });
    loop(i, N) {
        auto& [r, c, id] = a[i];
        if (c > i) v1.insert(v1.end(), c - i, id), v2.insert(v2.end(), c - i, 'L');
        if (c < i) v1.insert(v1.end(), i - c, id), v2.insert(v2.end(), i - c, 'R');
    }

    cout << (N = v1.size());
    loop(i, N) cout << '\n' << v1[i] << ' ' << v2[i];
    return 0;
}