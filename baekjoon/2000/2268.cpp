#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 1000000;

int N;
ll arr[max_N];
ll fenwick[max_N + 1];

ll read(int idx) {
    ll ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
void update(int idx, ll val) {
    while (idx <= N) {
        fenwick[idx] += val;
        idx += (idx & -idx);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int M; cin >> N >> M;
    while (M--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op) {
            ll gap = b - arr[a - 1];
            arr[a - 1] = b;
            update(a, gap);
        }
        else {
            if (a > b) swap(a, b);
            cout << read(b) - read(a - 1) << '\n';
        }
    }
    return 0;
}