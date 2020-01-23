#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

vector<P> adj[10001];
int max_h[10001];

// vertex의 모든 child를 조사해서
// 가장 큰 높이를 return
int cal_maxh(int vertex)
{
    if (adj[vertex].size() == 0) return 0;
    int& ret = max_h[vertex];
    if (ret != -1) return ret;

    for (auto x : adj[vertex]) {
        int child = x.first, dist = x.second;
        ret = max(ret, cal_maxh(child) + dist);
    }
    return ret;
}

// 가장 큰 cal_maxh 두개의 합을 return
int dia(int vertex)
{
    if (adj[vertex].size() < 2) return 0;
    vector<int> tmp;
    for (auto x : adj[vertex]) {
        int child = x.first, dist = x.second;
        tmp.push_back(cal_maxh(child) + dist);
    }
    sort(tmp.begin(), tmp.end(), greater<int>());
    return tmp[0] + tmp[1];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(max_h, -1, sizeof(max_h));
    int N; cin >> N;
    loop(i, N - 1) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
    }

    // dia를 계산할 때 child가 둘 이상인 것만 고려하므로
    // child가 1개인 root의 높이가 답이 될 경우를 고려해줘야 한다.
    int ans = cal_maxh(1);
    for (int i = 1; i <= N; ++i)
        ans = max(ans, dia(i));
    cout << ans;
    return 0;
}