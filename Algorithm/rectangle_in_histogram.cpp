#include<bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> h(N + 1);
    for (int i = 0; i < N; ++i)
        cin >> h[i];

    stack<int> stk;
    int ans = 0;
    for (int i = 0; i < N + 1; ++i) {
        while (!stk.empty() && h[stk.top()] >= h[i]) {
            int H = h[stk.top()]; stk.pop();
            int L = stk.empty() ? -1 : stk.top();
            ans = max(ans, H * (i - L - 1));
        }
        stk.emplace(i);
    }
    cout << ans;
    return 0;
}