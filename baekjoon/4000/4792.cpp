#include <iostream>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 1000;

int blue[max_N + 1], red[max_N + 1], MST[max_N + 1];

int find_rt(int u, int parent[])
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u], parent);
}
void union_tr(int u, int v, int parent[], int& cnt)
{
    u = find_rt(u, parent), v = find_rt(v, parent);
    if (u != v) {
        parent[u] = v;
        ++cnt;
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        int N, M, K; cin >> N >> M >> K;
        if (N == 0) break;
        LOOP(i, N) blue[i] = i;
        LOOP(i, N) red[i] = i;
        LOOP(i, N) MST[i] = i;
        int cnt_B = 0, cnt_R = 0, cnt_MST = 0;

        while (M--) {
            char c; int u, v;
            cin >> c >> u >> v;
            int* parent = (c == 'B' ? blue : red);
            int& cnt = (c == 'B' ? cnt_B : cnt_R);

            union_tr(u, v, MST, cnt_MST);
            union_tr(u, v, parent, cnt);
        }

        /*
            cnt_MST : red, blue 신경 끄고 spanning-tree를 만들 때 edge 개수
                      만약 N-1이 아니라면 애초에 spanning-tree를 만들 수 없다.
            cnt_R,B : red, blue만 이용해서 spanning-tree를 만들 때 edge 개수
                      만약 cnt_MST == N-1이라면
                      cnt_R : red edge를 최대한 사용해서 만든 spanning-tree의 red edge 개수
                             ( == blue를 최소한으로 사용)
                      cnt_B : blue edge를 최대한 사용해서 만든 spanning-tree의 blue edge 개수

            blue의 최소, 최대 범위 안에 K가 있어야 한다.
        */

        cout << (cnt_MST == N - 1 && (N - 1 - cnt_R <= K && K <= cnt_B)) << '\n';
    }

    return 0;
}