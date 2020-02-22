#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 10000;

tup DP[max_N + 1];

int sum(const tup& x) {
    auto [a, b, c] = x;
    return a + b + c;
}
int main() {
    DP[1] = { 1,0,0 };
    DP[2] = { 1,1,0 };
    DP[3] = { 1,1,1 };
    for (int i = 4; i <= max_N; ++i) {
        int one = get<0>(DP[i - 1]);
        int two = get<0>(DP[i - 2]) + get<1>(DP[i - 2]);
        int three = sum(DP[i - 3]);
        DP[i] = { one,two,three };
    }
    
    int T; cin >> T;
    while (T--) {
        int q; cin >> q;
        cout << sum(DP[q]) << '\n';
    }
    return 0;
}