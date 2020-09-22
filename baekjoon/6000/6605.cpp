#include <bits/stdc++.h>
using namespace std;

const int mx = 2e9;
const long long p[4] = {2, 3, 5, 7};
const char s[4][3] = {"th", "st", "nd", "rd"};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.emplace(1);

    vector<int> vt;
    while (vt.size() < 5842) {
        int x = pq.top();
        pq.pop();
        vt.emplace_back(x);

        for (int i = 0; i < 4; ++i) {
            if (x * p[i] > mx) break;
            pq.emplace(x * p[i]);
            if (x % p[i] == 0) break;
        }
    }

    for (int n;;) {
        cin >> n;
        if (!n) break;
        cout << "The " << n
             << ((n % 10 < 4 && (n / 10) % 10 != 1) ? s[n % 10] : "th")
             << " humble number is " << vt[n - 1] << ".\n";
    }
    return 0;
}