#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;
typedef long long ll;
const int max_N = 100000;

typedef struct {
    int num;
    int x, y, z;
} pos;

int parent[max_N];
tup E[(max_N - 1) * 3];
pos V[max_N];

bool cmp_x(pos& a, pos& b) { return a.x < b.x; }
bool cmp_y(pos& a, pos& b) { return a.y < b.y; }
bool cmp_z(pos& a, pos& b) { return a.z < b.z; }
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) parent[i] = i;
    loop(i, N) {
        V[i].num = i;
        cin >> V[i].x >> V[i].y >> V[i].z;
    }

    // x,y,z좌표끼리 가장 가까운 edge만 고려하면 된다.
    // 각각의 좌표로 정렬한 뒤 인접한 N-1개 edge를 E에 넣는다.
    int idx = 0;
    sort(V, V + N, cmp_x);
    loop(i, N - 1) E[idx++] = { V[i + 1].x - V[i].x,V[i].num,V[i + 1].num };
    sort(V, V + N, cmp_y);
    loop(i, N - 1) E[idx++] = { V[i + 1].y - V[i].y,V[i].num,V[i + 1].num };
    sort(V, V + N, cmp_z);
    loop(i, N - 1) E[idx++] = { V[i + 1].z - V[i].z,V[i].num,V[i + 1].num };
    
    // 정렬한 뒤 Kruskal
    sort(E, E + idx);
    ll ans = 0;
    loop(i, idx) {
        int u = get<1>(E[i]), v = get<2>(E[i]);
        u = find_rt(u), v = find_rt(v);
        if (u == v) continue;
        parent[u] = v;
        ans += get<0>(E[i]);
        --N;
        if (N == 1) break;
    }
    cout << ans;
    return 0;
}