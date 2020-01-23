#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;
const int max_N = 100000;

int dist(P a, P b)
{
    int dx = a.first - b.first, dy = a.second - b.second;
    return dx * dx + dy * dy;
}

P dots[max_N];
int main() {
    int N; cin >> N;
    loop(i, N) cin >> dots[i].first >> dots[i].second;
    sort(dots, dots + N);
    set<P> candidate = { dots[0],dots[1] };
    int ans = dist(dots[0], dots[1]);
    int start = 0;
    for (int i = 2; i < N; ++i) {
        P now = dots[i];
        while (start < i) {
            P p = dots[start];
            int x = now.first - p.first;
            if (x * x > ans) {
                candidate.erase(p);
                start += 1;
            }
            else break;
        }
        int d = (int)sqrt((double)ans) + 1;
        auto lower_point = P(-100000, now.second - d);
        auto upper_point = P(100000, now.second + d);
        auto lower = candidate.lower_bound(lower_point);
        auto upper = candidate.upper_bound(upper_point);
        for (auto it = lower; it != upper; it++) {
            int d = dist(now, *it);
            if (d < ans) ans = d;
        }
        candidate.insert(now);
    }
    cout << ans;
    return 0;
}