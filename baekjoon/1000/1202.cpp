#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
#define ll long long

P jew[300000];
int knap[300000];
class cmp
{
public:
    bool operator() (P& a, P& b)
    {
        return a.second < b.second;
    }
};

int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    int J, K;
    cin >> J >> K;
    loop(i, J) cin >> jew[i].first >> jew[i].second;
    loop(i, K) cin >> knap[i];
    sort(jew, jew + J);
    sort(knap, knap + K);

    int pos = 0;
    ll ans = 0;
    priority_queue<P, vector<P>, cmp> pq;
    loop(i, K) {
        // i번 가방에 들어가는 보석을 전부 pq에 집어넣음
        while (pos < J && jew[pos].first <= knap[i])
            pq.push(jew[pos++]);

        // pq.top == 가장 값어치가 높은 보석
        if (!pq.empty()) {
            ans += (ll)pq.top().second;
            pq.pop();
        }
    }
    cout << ans;
    return 0;
}