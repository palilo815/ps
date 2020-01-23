#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

P arr[200000];
auto cmp = [](P a, P b)
{
    return a.second < b.second;
};
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].first >> arr[i].second;
    
    // 뒤의 숙제부터 고려한다.
    sort(arr, arr + N, greater<P>());
    priority_queue<P, vector<P>, decltype(cmp)> pq(cmp);
    int day = arr[0].first, pos = 0, ans = 0;

    while (day) {
        // day일에 할 수 있는 숙제룰 전부 집어넣음
        while (pos < N && arr[pos].first >= day)
            pq.push(arr[pos++]);
        // 그 중에서 보상이 제일 큰 것을 한다.
        if (!pq.empty()) {
            ans += pq.top().second;
            pq.pop();
        }
        --day;
    }
    cout << ans;
    return 0;
}