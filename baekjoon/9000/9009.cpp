#include <bits/stdc++.h>
using namespace std;
const int max_n = 1000000000;
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> fibo{ 1,1 };
    while (1) {
        int tmp = fibo.end()[-1] + fibo.end()[-2];
        if (tmp > max_n) break;
        fibo.push_back(tmp);
    }

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        stack<int> ans;
        while (n) {
            auto it = upper_bound(fibo.begin(), fibo.end(), n);
            --it;
            ans.push(*it);
            n -= *it;
        }
        while (!ans.empty()) {
            cout << ans.top() << ' ';
            ans.pop();
        }
        cout << '\n';
    }
    return 0;
}