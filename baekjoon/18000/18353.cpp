#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    vector<int> T(1);
    int N; cin >> N >> T[0];

    for (int i = 1, x; i < N; ++i) {
        cin >> x;
        if (x < T.back()) T.emplace_back(x);
        else *lower_bound(T.begin(), T.end(), x, greater<int>()) = x;
    }
    cout << N - T.size();
    return 0;
}