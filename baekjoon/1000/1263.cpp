#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    priority_queue<P> pq;
    int n; cin >> n;
    while (n--) {
        int t, s; cin >> t >> s;
        pq.push({ s,t });
    }

    // curr : 가장 큰 마감 시작에서 시작
    // 거꾸로 0을 향해 줄여간다.
    int curr = pq.top().first;
    while (!pq.empty()) {
        int deadline = pq.top().first, cost = pq.top().second; pq.pop();
        if (deadline < curr) curr = deadline;
        curr -= cost;
    }
    if (curr < 0) curr = -1;
    cout << curr;
    return 0;
}