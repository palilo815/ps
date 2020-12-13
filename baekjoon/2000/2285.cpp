#include <bits/stdc++.h>
#define pos first
#define cnt second
using namespace std;

const int mxN = 1e5;

pair<int, int> city[mxN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    int64_t total = 0;
    for (int i = 0; i < n; ++i) {
        cin >> city[i].pos >> city[i].cnt;
        total += city[i].cnt;
    }

    sort(city, city + n, [&](auto& a, auto& b) {
        return a.pos < b.pos;
    });

    total = (total + 1) >> 1;
    int64_t sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += city[i].cnt;
        if (sum >= total) {
            cout << city[i].pos;
            break;
        }
    }
}