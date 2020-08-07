#include <bits/stdc++.h>
using namespace std;

const int mxN = 1001;

int* par, * cnt;
int blue[mxN], red[mxN], mst[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    for (int N, M, K;;) {
        cin >> N >> M >> K;
        if (N == 0) break;

        memset(blue + 1, -1, sizeof(int) * N);
        memset(red + 1, -1, sizeof(int) * N);
        memset(mst + 1, -1, sizeof(int) * N);
        int cnt_B = 0, cnt_R = 0, cnt_mst = 0;

        par = mst;
        for (int u, v, U, V; M--; par = mst) {
            char c; cin >> c >> U >> V;
            u = _find(U), v = _find(V);
            if (u ^ v) par[u] = v, ++cnt_mst;

            c == 'B' ? (par = blue, cnt = &cnt_B) : (par = red, cnt = &cnt_R);
            u = _find(U), v = _find(V);
            if (u ^ v) par[u] = v, ++*cnt;
        }
        /*
            cnt_mst : red, blue 신경 끄고 spanning-tree를 만들 때 edge 개수
                      만약 N-1이 아니라면 애초에 spanning-tree를 만들 수 없다.
            cnt_R,B : red, blue만 이용해서 spanning-tree를 만들 때 edge 개수
                      만약 cnt_mst == N-1이라면
                      cnt_R : red edge를 최대한 사용해서 만든 spanning-tree의 red edge 개수
                             ( == blue를 최소한으로 사용)
                      cnt_B : blue edge를 최대한 사용해서 만든 spanning-tree의 blue edge 개수

            blue의 최소, 최대 범위 안에 K가 있어야 한다.
        */
        cout << (cnt_mst == N - 1 && (N - 1 - cnt_R <= K && K <= cnt_B)) << '\n';
    }
    return 0;
}