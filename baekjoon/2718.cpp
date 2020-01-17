#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int cache[15][50];
int DP(int mask, int n)
{
    if (n == 0) {
        if (mask) return 0;
        else return 1;
    }
    int& ret = cache[mask][n];
    if (ret != -1) return ret;

    if (mask) {
        if (mask == 6) ret = DP(9, n - 1);
        else ret = DP(0, n - 1) + DP(mask ^ 15, n - 1);
    }
    else {
        ret = DP(6, n) + DP(0, n - 1) + DP(3, n - 1) + DP(12, n - 1);
        if (n > 1) ret += DP(0, n - 2);
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(cache, -1, sizeof(cache));
    loop(i, 16)
        // ....  ㅁㅁ..  ㅁ..ㅁ  ..ㅁㅁ 인 경우 빈 자리를 채울 수 있음
        if (i == 0 || i == 3 || i == 9 || i == 12) cache[i][1] = 1;
        // 위의 경우를 제외하곤 채울 수 없음
        else cache[i][1] = 0;
    
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << DP(0, n) << '\n';
    }
    return 0;
}