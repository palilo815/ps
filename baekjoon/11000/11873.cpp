#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int M = 1001;

int h[M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    h[0] = -1;
    stack<int> stk;
    stk.emplace(0);
start:;
    int R, C; cin >> R >> C;
    if (!R) return 0;

    memset(h + 1, 0, sizeof(int) * C);
    int ans = 0;

    while (R--) {
        LOOP(i, C) {
            int x; cin >> x;
            x ? ++h[i] : h[i] = 0;
        }
        LOOP(i, C) {
            while (h[stk.top()] >= h[i]) {
                int H = h[stk.top()]; stk.pop();
                ans = max(ans, H * (i - stk.top() - 1));
            }
            stk.emplace(i);
        }
        while (stk.size() != 1) {
            int H = h[stk.top()]; stk.pop();
            ans = max(ans, H * (C - stk.top()));
        }
    }
    cout << ans << '\n';
    goto start;
}