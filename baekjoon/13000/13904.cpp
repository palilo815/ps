#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;
const int max_N = 1000;

P HW[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
     
    priority_queue<P> pq;
    int N; cin >> N;
    // pq : { score, deadline }
    // HW : { deadline, score }
    // homework를 deadline 내림차순으로 정렬
    loop(i, N) cin >> HW[i].first >> HW[i].second;
    sort(HW, HW + N, greater<P>());

    // 마지막날부터 시작한다.
    // day = 현재 날짜
    int day = HW[0].first, i = 0, ans = 0;
    // day == 0이 될 때까지 반복
    while (day) {
        // day날에 할 수 있는 homework를 전부 pq에 집어넣는다.
        while (i < N && HW[i].first == day) {
            pq.push({ HW[i].second,HW[i].first });
            ++i;
        }
        // 그 중 가장 점수 높은 숙제를 해결
        if (!pq.empty()) {
            ans += pq.top().first;
            pq.pop();
        }
        --day;
    }
    cout << ans;
    return 0;
}