#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int road[1001];
int main()
{
    int n, ans = 0;
    cin >> n;
    loop(i, n) cin >> road[i];
    loop(bot, n - 1) {
        int top = bot;
        while (road[top + 1] > road[top]) ++top;
        ans = max(ans, road[top] - road[bot]);
        bot = top;
    }
    cout << ans;
    return 0;
}