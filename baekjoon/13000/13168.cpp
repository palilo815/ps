#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 100;
const int oo = 0x3f3f3f3f;

unordered_map<string, int> type = {
    {"Subway", 0},
    {"Bus", 1},
    {"Taxi", 2},
    {"Airplane", 3},
    {"KTX", 4},
    {"S-Train", 5},
    {"V-Train", 6},
    {"ITX-Saemaeul", 7},
    {"ITX-Cheongchun", 8},
    {"Mugunghwa", 9}
};
int d1[mxN][mxN], d2[mxN][mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, R; cin >> N >> R;
    unordered_map<string, int> mp;
    loop(i, N) {
        string s; cin >> s;
        mp[s] = i;
    }

    int M; cin >> M;
    vector<int> src(M);
    for (int& x : src) {
        string s; cin >> s;
        x = mp[s];
    }

    memset(d1, 0x3f, sizeof(d1));
    memset(d2, 0x3f, sizeof(d2));
    loop(i, N) d1[i][i] = d2[i][i] = 0;

    cin >> M;
    for (string a, b, c; M; --M) {
        int u, v, t, w;
        cin >> a >> b >> c >> w;
        w <<= 1;
        t = type[a], u = mp[b], v = mp[c];

        if (w < d1[u][v])
            d1[u][v] = d1[v][u] = w;
        if (t > 4)
            w = t > 6 ? 0 : (w >> 1);
        if (w < d2[u][v])
            d2[u][v] = d2[v][u] = w;
    }

    loop(k, N) loop(i, N) if (d1[i][k] ^ oo)
        loop(j, N) if (d1[k][j] ^ oo)
            d1[i][j] = min(d1[i][j], d1[i][k] + d1[k][j]);
    loop(k, N) loop(i, N) if (d2[i][k] ^ oo)
        loop(j, N) if (d2[k][j] ^ oo)
            d2[i][j] = min(d2[i][j], d2[i][k] + d2[k][j]);

    int ans1 = 0, ans2 = 0;
    loop(i, src.size() - 1) {
        ans1 += d1[src[i]][src[i + 1]];
        ans2 += d2[src[i]][src[i + 1]];
    }
    cout << (ans1 > ans2 + R * 2 ? "Yes" : "No");
    return 0;
}