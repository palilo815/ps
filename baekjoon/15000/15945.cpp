#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int _min = INT_MAX, _max = INT_MIN;
    int N; cin >> N;
    while (N--) {
        int x; cin >> x;
        if (x < _min) _min = x;
        if (x > _max) _max = x;
    }

    int ans = 0;
    if (_min > 0) ans = min(_min, _max - _min);
    if (_max < 0) ans = min(-_max, _max - _min);
    cout << ans;
    return 0;
}