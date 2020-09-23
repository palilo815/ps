#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;

int N;
string s;

int solve(int mul) {
    int ret = mul;
    while (N--) {
        cin >> s;
        if (s == "(")
            ret = mul ? ((ll)ret * solve(0) % mod) : ((ret + solve(1)) % mod);
        else if (s == ")")
            return ret;
        else {
            int n = stoi(s);
            ret = mul ? ((ll)ret * n % mod) : ((ret + n) % mod);
        }
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N;
    cout << solve(0);
    return 0;
}