#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_T = 200000;

set<int> block[max_T + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, T; cin >> N >> T;
    while (N--) {
        int x, y; cin >> x >> y;
        block[y].insert(x);
    }

    int ans = 0;
    queue<p> q;
    q.push({ 0,0 }), q.push({ -1,-1 });
    while (1) {
        auto [x, y] = q.front(); q.pop();
        if (y == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.push({ -1,-1 });
            continue;
        }
        if (y == T) break;

        for (int Y = y + 2; Y >= y - 2; --Y) {
            if (Y < 0 || Y > T) continue;
            auto it = block[Y].lower_bound(x - 2);
            auto hi = block[Y].upper_bound(x + 2);
            while (it != hi) {
                q.push({ *it,Y });
                it = block[Y].erase(it);
            }
        }
    }
    cout << ans;
    return 0;
}