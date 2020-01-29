#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_W = 100000;

// DP[w] : w의 무게로 얻을 수 있는 최대 가치
int DP[max_W + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, W; cin >> N >> W;
    while (N--) {
        int weight, value; cin >> weight >> value;
        for (int i = W - weight;i >= 0;--i)
            // 만약 i의 무게로 배낭을 채우는 경우가 있다면
            if (DP[i])
                // i + weight도 채울 수 있다.
                DP[i + weight] = max(DP[i + weight], DP[i] + value);
        // 이 물건 하나만 넣는 경우
        DP[weight] = max(DP[weight], value);
    }
    int ans = 0;
    loop(i, W + 1)
        ans = max(ans, DP[i]);
    cout << ans;
    return 0;
}