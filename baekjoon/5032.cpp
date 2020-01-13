#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int sum, a, b, c, count = 0, drink;
    cin >> a >> b >> c;
    sum = a + b;

    // drink : 새 음료, 매일 빈병/c 만큼 리필된다.
    // count : 마신 개수, drink만큼 매일 증가한다.
    // sum : 빈 병 개수
    while (sum >= c) {
        drink = sum / c;
        count += drink;
        sum -= drink * c;
        sum += drink;
    }
    cout << count;
    return 0;
}