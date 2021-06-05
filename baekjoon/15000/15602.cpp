#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<string> a(n);
    for (auto& x : a) cin >> x;

    vector<string> eg(n);

    int m;
    cin >> m;

    vector<int> correct(n), incorrect(n);
    for (string u, v, w; m--;) {
        cin >> u >> v >> w;
        for (int i = 0; i < n; ++i)
            if (a[i] == u) {
                ++(w[0] == 'c' ? correct[i] : incorrect[i]);
                eg[i] = v;
            }
    }

    bool only = true;
    for (int i = 0; i < n; ++i)
        if (correct[i] + incorrect[i] != 1)
            only = false;

    if (only) {
        for (const auto& x : eg) cout << x << ' ';
        cout << (all_of(correct.begin(), correct.end(), [&](auto& x) { return x; }) ? "\ncorrect" : "\nincorrect");
        return 0;
    }

    int64_t good = accumulate(correct.begin(), correct.end(), 1ll, multiplies<int64_t>());
    transform(incorrect.begin(), incorrect.end(), correct.begin(), correct.begin(), plus<int>());
    int64_t total = accumulate(correct.begin(), correct.end(), 1ll, multiplies<int64_t>());

    cout << good << " correct\n";
    cout << total - good << " incorrect";
}