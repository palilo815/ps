#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 50;

int ans, N_house, N_bbq;
vector<P> house, BBQ;
vector<int> vt;
int chicken_dist()
{
    int ret = 0;
    for (P p : house) {
        int dist = INT_MAX;
        for (int i : vt)
            dist = min(dist, abs(BBQ[i].first - p.first) + abs(BBQ[i].second - p.second));
        ret += dist;
    }
    return ret;
}
void select(int M, int prev_idx)
{
    if (M == 0) {
        ans = min(ans, chicken_dist());
        return;
    }
    for (int i = prev_idx + 1; i < N_bbq - M + 1; ++i) {
        vt.push_back(i);
        select(M - 1, i);
        vt.pop_back();
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ans = INT_MAX;
    int N, M; cin >> N >> M;
    loop(i, N) loop(j, N) {
        int x; cin >> x;
        if (x == 1)
            house.push_back({ i,j });
        else if (x == 2)
            BBQ.push_back({ i,j });
    }
    N_house = house.size();
    N_bbq = BBQ.size();
    select(M, -1);
    cout << ans;
    return 0;
}