#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    vector<p> order;
    string q;
    int Q, N; cin >> Q >> N;
    while (Q--) {
        cin >> q;
        if (q[0] == 'o') {
            int n, t; cin >> n >> t;
            order.emplace_back(t, n);
        }
        else if (q[0] == 's')
            sort(order.begin(), order.end());
        else {
            int n; cin >> n;
            for (auto it = order.begin(); it != order.end(); ++it)
                if (it->second == n) {
                    order.erase(it);
                    break;
                }
        }
        if (order.empty()) cout << "sleep";
        else for (auto [t, n] : order) cout << n << ' ';
        cout << '\n';
    }
    return 0;
}