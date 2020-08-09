#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int x[26], y[26];

int ccw(int i, int j, int k) {
    int ret = (x[j] - x[i]) * (y[k] - y[i]) - (y[j] - y[i]) * (x[k] - x[i]);
    return ret ? (ret > 0 ? 1 : -1) : 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) loop(j, N) {
        char c; cin >> c;
        if (c != '.')
            x[c - 'A'] = i + 1, y[c - 'A'] = j + 1;
    }

    int ans = 0;
    loop(i, 26) if (x[i])
        loop(j, i) if (x[j])
            loop(k, j) if (x[k])
                ans += ccw(i, j, k) == 0;
    cout << ans;
    return 0;
}