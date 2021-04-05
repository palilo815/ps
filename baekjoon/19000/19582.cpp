#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    // dp0 : 모두 다 참가했을 때 받는 상금 최솟값
    // dp1 : 하나 빼고 다 참가했을 때 상금 최솟값
    int dp0 = 0, dp1 = 0;
    constexpr int INF = 0x3f3f3f3f;
    for (int i = n, x, p; i--;) {
        cin >> x >> p;
        dp1 = dp1 > x ? dp0 : min({INF, dp0, dp1 + p});
        dp0 = dp0 > x ? INT_MAX : min(INF, dp0 + p);
    }
    cout << (const string[]) {"Kkeo-eok", "Zzz"}[dp1 == INT_MAX];
}