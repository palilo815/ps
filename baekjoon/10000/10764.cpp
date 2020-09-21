#include <bits/stdc++.h>
#define _1 mat[i][j]
#define _2 mat[i][j + 1]
#define _3 mat[i][j + 2]
#define _4 mat[i + 1][j]
#define _5 mat[i + 1][j + 1]
#define _6 mat[i + 1][j + 2]
#define _7 mat[i + 2][j]
#define _8 mat[i + 2][j + 1]
#define _9 mat[i + 2][j + 2]
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

char mat[50][50];
int cnt[26][26];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    loop(i, N) loop(j, M) cin >> mat[i][j];
    loop(i, N) loop(j, M) mat[i][j] -= 'A';

    loop(i, N) loop(j, M - 2) {
        if (_1 != _2 && _2 == _3)
            ++cnt[_1][_3];
        if (_1 == _2 && _2 != _3)
            ++cnt[_3][_1];
    }
    loop(i, N - 2) loop(j, M) {
        if (_1 != _4 && _4 == _7)
            ++cnt[_1][_7];
        if (_1 == _4 && _4 != _7)
            ++cnt[_7][_1];
    }
    loop(i, N - 2) loop(j, M - 2) {
        if (_1 != _5 && _5 == _9)
            ++cnt[_1][_9];
        if (_1 == _5 && _5 != _9)
            ++cnt[_9][_1];
        if (_3 != _5 && _5 == _7)
            ++cnt[_3][_7];
        if (_3 == _5 && _5 != _7)
            ++cnt[_7][_3];
    }
    loop(i, 26) cnt['M' - 'A'][i] = 0;
    loop(i, 26) cnt[i]['O' - 'A'] = 0;
    cout << *max_element(cnt[0], cnt[26]);
    return 0;
}