#include <bits/stdc++.h>
using namespace std;
struct elem {
    int A, B;
};

const int mxN = 1e5;

elem a[mxN];
int p[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> a[i].A >> a[i].B;

    sort(a, a + N, [&](auto & a, auto & b) {
        return a.A < b.A;
    });

    vector<int> T = {a[0].B};
    for (int i = 1; i < N; ++i) {
        if (a[i].B > T.back()) {
            p[i] = T.size();
            T.emplace_back(a[i].B);
        }
        else {
            auto it = lower_bound(T.begin(), T.end(), a[i].B);
            p[i] = it - T.begin();
            *it = a[i].B;
        }
    }

    for (int i = N - 1, pos = T.size() - 1; ~pos; --i)
        if (p[i] == pos) {
            p[i] = -1;
            --pos;
        }

    cout << N - T.size();
    for (int i = 0; i < N; ++i)
        if (~p[i])
            cout << '\n' << a[i].A;
    return 0;
}