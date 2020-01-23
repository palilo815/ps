#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool is_clock(int num)
{
    int tmp = num;
    // 0이 있으면 탈락
    loop(i, 4) {
        if (tmp % 10 == 0) return false;
        tmp /= 10;
    }
    
    // num을 회전시켰을 때 더 작은 수가 나왔다면 탈락
    tmp = num;
    loop(i, 3) {
        tmp = (tmp % 10) * 1000 + tmp / 10;
        if (tmp < num) return false;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int num = 0;
    loop(i, 4) {
        int x; cin >> x;
        num = 10 * num + x;
    }

    // num을 가장 작은 시계수로 만드는 과정
    int tmp = num;
    loop(i, 3) {
        tmp = (tmp % 10) * 1000 + tmp / 10;
        num = min(num, tmp);
    }

    // num보다 작은 시계수를 일일히 찾는다.
    int ans = 1;
    for (int i = 1111;i < num;++i)
        if (is_clock(i)) ++ans;
    cout << ans;
    return 0;
}