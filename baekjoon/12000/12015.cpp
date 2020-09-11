#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    vector<int> T = {INT_MIN};

    int N; cin >> N;
    for (int x; N--;) {
        cin >> x;
        if (x > T.back()) T.emplace_back(x);
        else *lower_bound(T.begin(), T.end(), x) = x;
    }
    cout << T.size() - 1;
    return 0;
}