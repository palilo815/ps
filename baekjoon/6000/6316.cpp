#include <bits/stdc++.h>
using namespace std;

struct elem {
    int d, mx, my, bx, by;
    elem(int d, int mx, int my, int bx, int by) : d(d), mx(mx), my(my), bx(bx), by(by) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

constexpr int MX_N = 20;

char grid[MX_N][MX_N];
int dist[MX_N][MX_N][MX_N][MX_N];
char op[MX_N][MX_N][MX_N][MX_N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    constexpr char operations[] = "nwesNWES";
    constexpr int offset = 1 << 16;

    array<int, 23> table;
    table['n' - 'a'] = 0, table['w' - 'a'] = 1, table['e' - 'a'] = 2, table['s' - 'a'] = 3;

    int TC = 0;

TOP:;
    int n, m;
    cin >> n >> m;
    if (!n && !m) return 0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];

    int man_sx = -1, man_sy = -1, box_sx = -1, box_sy = -1, end_sx = -1, end_sy = -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S')
                man_sx = i, man_sy = j;
            else if (grid[i][j] == 'B')
                box_sx = i, box_sy = j;
            else if (grid[i][j] == 'T')
                end_sx = i, end_sy = j;
        }

    memset(dist, 0x3f, sizeof(dist));
    dist[man_sx][man_sy][box_sx][box_sy] = 0;
    op[man_sx][man_sy][box_sx][box_sy] = '#';

    priority_queue<elem> pq;
    pq.emplace(0, man_sx, man_sy, box_sx, box_sy);

    int man_ex = -1, man_ey = -1;
    while (!pq.empty()) {
        const auto [d, mx, my, bx, by] = pq.top();
        pq.pop();

        if (d != dist[mx][my][bx][by]) continue;
        if (bx == end_sx && by == end_sy) {
            man_ex = mx, man_ey = my;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            const auto& [dx, dy] = mov[i];
            const auto mx2 = mx + dx, my2 = my + dy;
            if (mx2 == -1 || mx2 == n || my2 == -1 || my2 == m || grid[mx2][my2] == '#') continue;

            const bool pushed = (bx == mx2 && by == my2);
            const auto bx2 = bx + (pushed ? dx : 0), by2 = by + (pushed ? dy : 0);
            if (bx2 == -1 || bx2 == n || by2 == -1 || by2 == m || grid[mx2][my2] == '#') continue;

            if (auto d2 = d + (pushed ? offset : 1); dist[mx2][my2][bx2][by2] > d2) {
                pq.emplace(dist[mx2][my2][bx2][by2] = d2, mx2, my2, bx2, by2);
                op[mx2][my2][bx2][by2] = operations[i + (pushed ? 4 : 0)];
            }
        }
    }

    cout << "Maze #" << ++TC << '\n';
    if (~man_ex && ~man_ey) {
        string trace = "";
        for (int x1 = man_ex, y1 = man_ey, x2 = end_sx, y2 = end_sy, t; op[x1][y1][x2][y2] != '#';) {
            const auto& c = op[x1][y1][x2][y2];
            trace += c;
            if (isupper(c)) {
                const int t = table[c - 'A'];
                x1 -= mov[t].first, y1 -= mov[t].second;
                x2 -= mov[t].first, y2 -= mov[t].second;
            } else {
                const int t = table[c - 'a'];
                x1 -= mov[t].first, y1 -= mov[t].second;
            }
        }
        reverse(trace.begin(), trace.end());
        cout << trace << '\n';
    } else {
        cout << "Impossible.\n";
    }
    cout << '\n';
    goto TOP;
}