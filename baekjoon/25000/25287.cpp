#include <bits/stdc++.h>

int a[50000];

void run() {
    using namespace std;
    int n;
    cin >> n;
    for (int i {}; i < n; ++i) {
        cin >> a[i];
    }
    auto ok {true};
    for (int i {}, prv {}, cur; i < n; ++i, prv = cur) {
        cur = INT_MAX;
        if (a[i] >= prv) cur = a[i];
        const auto x {n - a[i] + 1};
        if (x >= prv && x < cur) cur = x;
        prv = cur;
        if (cur == INT_MAX) {
            ok = false;
            break;
        }
    }
    cout << (ok ? "YES" : "NO") << '\n';
}

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) run();
}
