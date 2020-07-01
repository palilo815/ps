#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

struct meteo {
    int l, r, w;
};

const int MAX = 300000;

int N, M, Q;
vector<int> state[MAX];
int req[MAX];
ll fenwick[MAX + 1];

meteo q[MAX];
int lo[MAX], hi[MAX];
vector<int> vt[MAX];

void update(int i, int v) {
    for (++i; i <= M; i += i & -i)
        fenwick[i] += v;
}
ll read(int i) {
    ll ret = 0;
    for (++i; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
bool go() {
    memset(fenwick + 1, 0, sizeof(ll) * M);
    loop(i, Q) vt[i].clear();

    bool ret = false;
    loop(i, N) if (lo[i] ^ hi[i]) {
        vt[(lo[i] + hi[i]) >> 1].emplace_back(i);
        ret = true;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> M;
    loop(i, M) {
        int x; cin >> x;
        state[x - 1].emplace_back(i);
    }
    loop(i, N) cin >> req[i];
    cin >> Q;
    loop(i, Q) {
        cin >> q[i].l >> q[i].r >> q[i].w;
        --q[i].l;
    }
    fill(hi, hi + N, Q);

    while (go()) loop(m, Q) {
        auto& [l, r, w] = q[m];
        if (l < r) update(l, w), update(r, -w);
        else update(0, w), update(r, -w), update(l, w);

        for (int& i : vt[m]) {
            ll total = 0;
            for (int& area : state[i]) {
                total += read(area);
                if (total >= req[i]) break;
            }
            total < req[i] ? (lo[i] = m + 1) : (hi[i] = m);
        }
    }

    loop(i, N) {
        if (lo[i] == Q) cout << "NIE";
        else cout << lo[i] + 1;
        cout << '\n';
    }
    return 0;
}