/*
    By himanshujaju
    https://codeforces.com/blog/entry/45578
*/
#include <bits/stdc++.h>
#define loop(i,s,e) for(auto i=s-(s>e);i!=e-(s>e);i+=1-2*(s>e))
using namespace std;

typedef long long ll;
const int max_N = 300000;

vector<int> owner[max_N + 1];
ll req[max_N + 1];

int ql[max_N + 1], qr[max_N + 1], qa[max_N + 1];

int lo[max_N + 1], hi[max_N + 1];
stack<int> stk[max_N + 1];

ll fenwick[max_N + 1];
int N, M;

void update(int idx, int val) {
    while (idx <= M) {
        fenwick[idx] += val;
        idx += (idx & -idx);
    }
}
ll read(int idx) {
    ll ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
void apply(int x) {
    if (ql[x] <= qr[x]) {
        update(ql[x], qa[x]);
        update(qr[x] + 1, -qa[x]);
    }
    else {
        update(1, qa[x]);
        update(qr[x] + 1, -qa[x]);
        update(ql[x], qa[x]);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    loop(i, 1, M + 1) {
        int x; cin >> x;
        owner[x].emplace_back(i);
    }
    loop(i, 1, N + 1)
        cin >> req[i];

    int Q; cin >> Q;
    loop(i, 1, Q + 1)
        cin >> ql[i] >> qr[i] >> qa[i];
    loop(i, 1, N + 1)
        lo[i] = 1, hi[i] = Q + 1;

    while (1) {
        memset(fenwick, 0, sizeof(fenwick));
        bool finished = true;

        loop(i, 1, N + 1)
            if (lo[i] != hi[i]) {
                stk[(lo[i] + hi[i]) / 2].emplace(i);
                finished = false;
            }
        if (finished) break;

        loop(q, 1, Q + 1) {
            apply(q);
            while (!stk[q].empty()) {
                int id = stk[q].top();
                stk[q].pop();

                ll sum = 0;
                for (auto sectors : owner[id]) {
                    sum += read(sectors);
                    if (sum >= req[id]) break;
                }

                if (sum >= req[id]) hi[id] = q;
                else lo[id] = q + 1;
            }
        }
    }
    loop(i, 1, N + 1)
        if (lo[i] <= Q) cout << lo[i] << '\n';
        else cout << "NIE\n";
    return 0;
}