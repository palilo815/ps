#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int x, y, t, min_x, min_y, dist = INT_MAX;
    cin >> x >> y >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        int tmp = abs(x - a) + abs(y - b);
        if (tmp < dist) {
            min_x = a, min_y = b; dist = tmp;
        }
    }
    cout << min_x << ' ' << min_y;
    return 0;
}