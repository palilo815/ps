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
    sort(acid.begin(), acid.end());
    sort(base.begin(), base.end());

    int A = 1e9 + 1, B = 1e9 + 1;
    if (acid.size() >= 2)
        B = acid[0], A = acid[1];
    if (base.size() >= 2 && base[0] + base[1] < abs(A + B))
        B = -base[1], A = -base[0];

    for (int a : acid) {
        auto it = lower_bound(base.begin(), base.end(), a);
        if (it != base.end()) {
            int b = -(*it);
            if (abs(a + b) < abs(A + B))
                A = a, B = b;
        }
        if (it != base.begin()) {
            --it;
            int b = -(*it);
            if (abs(a + b) < abs(A + B))
                A = a, B = b;
        }
    }
    cout << B << ' ' << A;
    return 0;
}