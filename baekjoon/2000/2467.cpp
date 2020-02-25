#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> acid, base;
    int N; cin >> N;
    while (N--) {
        int x; cin >> x;
        if (x > 0) acid.push_back(x);
        else base.push_back(-x);
    }
    reverse(base.begin(), base.end());

    if (acid.empty()) {
        cout << -base[1] << ' ' << -base[0];
        return 0;
    }
    if (base.empty()) {
        cout << acid[0] << ' ' << acid[1];
        return 0;
    }

    int A = 1e9 + 1, B = 1e9 + 1;
    for (int a : acid) {
        auto it = lower_bound(base.begin(), base.end(), a);

        if (it == base.end()) continue;
        int b = -(*it);
        if (abs(a + b) < abs(A + B))
            A = a, B = b;

        if (it == base.begin()) continue;
        --it;

        b = -(*it);
        if (abs(a + b) < abs(A + B))
            A = a, B = b;
    }
    cout << B << ' ' << A;
    return 0;
}