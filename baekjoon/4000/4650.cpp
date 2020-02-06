#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;
const int max_N = 26;

int parent[max_N];
vector<tup> road;
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    while (1) {
        int N; cin >> N;
        if (N == 0) break;
        loop(i, N) parent[i] = i;
        road.clear();

        char a, b;
        int M, w;
        loop(i, N - 1) {
            cin >> a >> M;
            loop(j, M) {
                cin >> b >> w;
                road.push_back({ w,a - 'A',b - 'A' });
            }
        }
        sort(road.begin(), road.end());

        int ans = 0;
        for (tup r : road) {
            int u = get<1>(r), v = get<2>(r);
            u = find_rt(u), v = find_rt(v);
            if (u == v) continue;
            parent[u] = v;
            ans += get<0>(r);
        }
        cout << ans << '\n';
    }
    return 0;
}