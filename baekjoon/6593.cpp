#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int Fl, row, col;
char Building[30][30][30];
int mov_z[6] = { -1,1,0,0,0,0 }, mov_y[6] = { 0,0,-1,1,0,0 }, mov_x[6] = { 0,0,0,0,-1,1 };

void BFS(int sF, int sR, int sC, int eF, int eR, int eC)
{
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(sF, sR, sC));
    q.push(make_tuple(-1, -1, -1));
    int ans = 0;
    bool escape = true;
    while (1) {
        int f = get<0>(q.front()), r = get<1>(q.front()), c = get<2>(q.front()); q.pop();
        if (f == -1) {
            if (q.empty()) {
                escape = false;
                break;
            }
            ++ans;
            q.push(make_tuple(-1, -1, -1));
            continue;
        }
        else if (f == eF && r == eR && c == eC) break;
        loop(i, 6) {
            int F = f + mov_z[i], R = r + mov_y[i], C = c + mov_x[i];
            if (F < 0 || F >= Fl || R < 0 || R >= row || C < 0 || C >= col || Building[F][R][C] == '#') continue;
            Building[F][R][C] = '#';
            q.push(make_tuple(F, R, C));
        }
    }
    if (escape) cout << "Escaped in " << ans << " minute(s).\n";
    else cout << "Trapped!\n";
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int sF, sR, sC, eF, eR, eC;
    char c;
    while (cin >> Fl >> row >> col) {
        if (Fl == 0) break;
        loop(i, Fl) loop(j, row) loop(k, col) {
            cin >> c;
            if (c == 'S') sF = i, sR = j, sC = k;
            else if (c == 'E') eF = i, eR = j, eC = k;
            Building[i][j][k] = c;
        }
        BFS(sF, sR, sC, eF, eR, eC);
    }
    return 0;
}