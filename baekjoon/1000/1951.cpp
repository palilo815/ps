#include<bits/stdc++.h>
using namespace std;
#define MOD 1234567
int main()
{
    int n, ans = 0, t = 0;
    cin >> n;
    while (1) {
        int tmp = n - pow(10, t++) + 1;
        if (tmp <= 0) break;
        ans = (ans + tmp) % MOD;
    }
    cout << ans;
    return 0;
}