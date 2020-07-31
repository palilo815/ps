#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 1000;

int N, a[mx][mx];
char d[mx][mx], v[mx][mx];

bool solve() {
    bool flag = false, cycle = false;
    loop(r, N) loop(c, N) if (!v[r][c]) {
        int i = r, j = c;
        for (v[i][j] = 's';; v[i][j] = '.') {
            switch (d[i][j]) {
            case 'U': i -= a[i][j]; break;
            case 'D': i += a[i][j]; break;
            case 'L': j -= a[i][j]; break;
            default : j += a[i][j];
            }
            if (v[i][j]) break;
        }
        if (v[i][j] == 's') {
            if (cycle) return true;
            cycle = true;
        }
        else if (v[i][j] == 'S') v[i][j] = '.';
        else if (flag) return true;
        else flag = true;
        if (r ^ i || c ^ j) v[r][c] = 'S';
    }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) loop(j, N) cin >> a[i][j] >> d[i][j];

    if (solve()) cout << "TOO SAFE";
    else {
        int sr = -1, sc = -1;
        loop(i, N) loop(j, N) if (v[i][j] == 'S') {
            if (~sr) {cout << "TOO SAFE"; return 0;}
            sr = i, sc = j;
        }
        if (~sr) cout << sr + 1 << ' ' << sc + 1;
        else cout << "THIEF LOVE IT!";
    }
    return 0;
}