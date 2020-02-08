#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 10;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int row, col;
int mat[max_N][max_N];

void flood_fill(int r, int c, int num)
{
    mat[r][c] = num;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || mat[R][C] != -1) continue;
        flood_fill(R, C, num);
    }
}
int find_rt(int u, vector<int>& parent)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u], parent);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 일단 육지를 -1로 받는다.
    cin >> row >> col;
    loop(i, row) loop(j, col) {
        int x; cin >> x;
        if (x) mat[i][j] = -1;
    }

    // flood_fill을 이용
    // 육지에 1, 2, 3,... 번호를 매긴다.
    int num = 0;
    loop(i, row) loop(j, col)
        if (mat[i][j] == -1) flood_fill(i, j, ++num);

    // 다리 정보를 받는다.
    vector<tup> edge;
    // 가로 방향 다리
    loop(r, row) {
        int prev = 0, dist = 0;
        loop(c, col) {
            // 물을 만나면 길이 증가
            if (mat[r][c] == 0) ++dist;
            else {
                // 육지이며, 이전에 만난 섬과 다른 번호이며, 처음 만난 섬이 아니고, 길이가 2 이상이어야 한다.
                if (mat[r][c] != prev && prev != 0 && dist >= 2)
                    edge.push_back({ dist,mat[r][c],prev });
                prev = mat[r][c];
                dist = 0;
            }
        }
    }
    // 세로 방향 다리
    loop(c, col) {
        int prev = 0, dist = 0;
        loop(r, row) {
            if (mat[r][c] == 0) ++dist;
            else {
                if (mat[r][c] != prev && prev != 0 && dist >= 2)
                    edge.push_back({ dist,mat[r][c],prev });
                prev = mat[r][c];
                dist = 0;
            }
        }
    }
    sort(edge.begin(), edge.end());

    // Kruskal MST
    vector<int> parent(num + 1);
    loop(i, num + 1) parent[i] = i;

    int ans = 0;
    for (tup bridge : edge) {
        int d = get<0>(bridge), u = get<1>(bridge), v = get<2>(bridge);
        u = find_rt(u, parent), v = find_rt(v, parent);
        if (u != v) {
            ans += d;
            parent[u] = v;
        }
    }

    // MST가 아니면 ans를 -1로 바꿔준다.
    int p = find_rt(1, parent);
    for (int i = 2; i <= num; ++i)
        if (find_rt(i, parent) != p) ans = -1;
    cout << ans;
    return 0;
}