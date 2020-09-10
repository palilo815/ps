#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    stack<int> stk;
    stk.emplace(INT_MAX);

    int N; cin >> N;
    long long ans = 0;
    for (int x; N--;) {
        cin >> x;
        while (stk.top() <= x) {
            stk.pop();
            ans += min(stk.top(), x);
        }
        stk.emplace(x);
    }

    while (stk.size() > 2) {
        stk.pop();
        ans += stk.top();
    }
    cout << ans;
    return 0;
}