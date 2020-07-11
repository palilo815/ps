#include <bits/stdc++.h>
using namespace std;

const int max_N = 3e5 + 1;
const int max_C = 1e4 + 1;

int a[max_N];
vector<int> hat[max_C];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    srand(time(0));

    int N, C; cin >> N >> C;
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
        hat[a[i]].emplace_back(i);
    }

    int Q; cin >> Q;
    while (Q--) {
        int l, r; cin >> l >> r;
        int half = (r - l + 1) / 2;
        for (int i = 0; i < 50; ++i) {
            int c = a[rand() % (r - l + 1) + l];
            if (upper_bound(hat[c].begin(), hat[c].end(), r) - lower_bound(hat[c].begin(), hat[c].end(), l) > half) {
                cout << "yes " << c << '\n';
                half = -1;
                break;
            }
        }
        if (~half) cout << "no\n";
    }
    return 0;
}