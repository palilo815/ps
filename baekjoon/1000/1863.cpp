#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    int ans = -1;

    stack<int> stk;
    stk.emplace(0);

    for (int _, h; N--;) {
        cin >> _ >> h;
        while (h < stk.top()) {
            ++ans;
            stk.pop();
        }
        if (h > stk.top()) stk.emplace(h);
    }
    cout << ans + stk.size();
    return 0;
}