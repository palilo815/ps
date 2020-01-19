#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll cache[31][61];
ll DP(int whole, int half)
{
    ll& ret = cache[whole][half];
    if (ret != -1) return ret;

    // whole이 하나도 없다면, 남은 날은 계속 half만 먹어야 하므로 경우의 수는 1이다.
    if (whole == 0) return ret = 1;

    if (half > 0) return ret = DP(whole - 1, half + 1) + DP(whole, half - 1);
    else return ret = DP(whole - 1, half + 1);
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    int n;
    while (1) {
        cin >> n;
        if (n == 0) break;
        cout << DP(n, 0) << '\n';
    }
    return 0;
}