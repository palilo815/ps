#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ans : 총 먹은 치킨
    // n : 주문할 수 있는 치킨
    // stamp : 가지고 있는 쿠폰
    int n, k;
    while (cin >> n >> k) {
        int ans = 0, stamp = 0;
        while (n) {
            ans += n;		// n마리 시켜서 먹는다
            stamp += n;		// 쿠폰을 n개 받음
            n = (stamp / k);// 쿠폰 k당 1마리를 더 시킬 수 있다.
            stamp -= k * n;	// n마리 시키고 남은 쿠폰
        }
        cout << ans << '\n';
    }
    return 0;
}