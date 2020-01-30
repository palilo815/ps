#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 100000;

int price[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> price[i];
    price[N] = INT_MAX;
    sort(price, price + N + 1, greater<int>());
    
    // 3번째 식품은 2+1으로 공짜로 얻는다.
    // 이때 나머지 계산을 편리하게 하기 위해
    // price[0] = INT_MAX를 집어넣었다.
    int ans = 0;
    for (int i = 1; i <= N; ++i)
        if (i % 3) ans += price[i];
    cout << ans;
    return 0;
}