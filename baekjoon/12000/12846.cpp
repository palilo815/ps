#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
typedef long long ll;

const int  max_N = 100000;

int pay[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    LOOP(i, N) cin >> pay[i];

    stack<int> stk;
    stk.emplace(0);

    ll ans = 0;
    LOOP(i, N) {
        while (pay[stk.top()] >= pay[i]) {
            ll p = pay[stk.top()]; stk.pop();
            ans = max(ans, p * (i - stk.top() - 1));
        }
        stk.emplace(i);
    }
    while (stk.size() != 1) {
        ll p = pay[stk.top()]; stk.pop();
        ans = max(ans, p * (N - stk.top()));
    }
    cout << ans;
    return 0;
}