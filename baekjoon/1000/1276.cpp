#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 100;

tup arr[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        auto& [y, x1, x2] = arr[i];
        cin >> y >> x1 >> x2;
    }
    sort(arr, arr + N, greater<tup>());
    arr[N] = { 0,INT_MIN,INT_MAX };

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        auto [y, x1, x2] = arr[i];
        int l = -1, r = -1, j = i + 1;
        while (y == get<0>(arr[j])) ++j;
        while (j <= N && (l == -1 || r == -1)) {
            auto [Y, X1, X2] = arr[j];
            if (l == -1 && (X1 <= x1 && x1 < X2)) l = Y;
            if (r == -1 && (X1 < x2 && x2 <= X2)) r = Y;
            ++j;
        }
        ans += (y - l) + (y - r);
    }
    cout << ans;
    return 0;
}