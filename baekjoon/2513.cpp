#include <bits/stdc++.h>
#define P pair<int,int>
using namespace std;

int solve(priority_queue<P>& pq, int bus_size)
{
    int ret = 0;
    while (!pq.empty()) {
        // dist : 가장 먼 집의 거리
        // bus : 현재 타고 있는 학생 수
        int dist = pq.top().first, bus = pq.top().second; pq.pop();
        if (bus > bus_size)
            pq.push({ dist,bus - bus_size });
        else
            while (!pq.empty()) {
                int pos = pq.top().first, num = pq.top().second; pq.pop();
                bus += num;
                if (bus > bus_size) {
                    pq.push({ pos,bus - bus_size });
                    break;
                }
            }
        ret += dist * 2;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, bus_size, school; cin >> N >> bus_size >> school;

    // 학교 기준 왼쪽 집과 오른쪽 집
    priority_queue<P> L, R;
    while (N--) {
        // pq에 해당 집까지의 거리와, 사는 학생 수를 넣는다.
        int pos, num; cin >> pos >> num;
        if (pos < school) L.push({ school - pos,num });
        else R.push({ pos - school,num });
    }

    int ans = 0;
    ans += solve(L, bus_size);
    ans += solve(R, bus_size);
    cout << ans;
    return 0;
}