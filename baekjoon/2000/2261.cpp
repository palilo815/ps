#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 100000;
p dot[max_N];

auto cmp_y = [](p a, p b)
{
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
};
int dist(p a, p b)
{
    int dx = a.first - b.first, dy = a.second - b.second;
    return dx * dx + dy * dy;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 출처)
    // https://www.acmicpc.net/blog/view/25

    int N; cin >> N;
    loop(i, N) cin >> dot[i].first >> dot[i].second;
    sort(dot, dot + N);

    set<p, decltype(cmp_y)> st(cmp_y);
    st.insert(dot[0]), st.insert(dot[1]);
    int ans = dist(dot[0], dot[1]);
    int start = 0;

    for (int i = 2; i < N; ++i) {
        p& here = dot[i];
        while (start < i) {
            int dx = dot[start].first - here.first;
            if (dx * dx > ans) st.erase(dot[start++]);
            else break;
        }

        int d = ceil(sqrt(ans));
        p lower_p = { -10000,here.second - d };
        p upper_p = { 10000,here.second + d };
        auto lower = st.lower_bound(lower_p);
        auto upper = st.upper_bound(upper_p);

        for (auto it = lower; it != upper; ++it) {
            int d = dist(here, *it);
            if (d < ans) ans = d;
        }
        st.insert(here);
    }
    cout << ans;
    return 0;
}