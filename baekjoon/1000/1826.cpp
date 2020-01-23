#include <iostream>
#include <algorithm>
#include <queue>
#define P pair<int,int>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

P gas_st[10000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> gas_st[i].first >> gas_st[i].second;
    sort(gas_st, gas_st + N);
    int dst, fuel; cin >> dst >> fuel;

    // pq에 지나온 주유소에서 채울 수 있었던 연료량을 넣는다.
    priority_queue<int> pq;
    int ans = 0, pos = 0;

    // 연료 1당 거리 1이므로, fuel가 곧 distance다.
    while (fuel < dst) {
        // pq에 지나온 주유소에서 채울 수 있었던 연료량을 넣는다.
        while (pos < N && gas_st[pos].first <= fuel)
            pq.push(gas_st[pos++].second);

        // 아직 도착하지 않았는데, 채울 연료가 없으면 실패
        if (pq.empty()) {
            ans = -1; break;
        }

        // 가장 많은 연료를 넣고 전진
        fuel += pq.top(); pq.pop();
        ++ans;
    }
    cout << ans;
    return 0;
}