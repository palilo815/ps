#include <iostream>
using namespace std;
typedef long long ll;

const int max_N = 150001;

int N;
ll odd[max_N];
ll even[max_N];

void update(int i, int v) {
    ll* fenwick = (i++ & 1 ? odd : even);
    for (i /= 2; i <= (N + 1) / 2; i += i & -i)
        fenwick[i] += v;
}
ll read(int i) {
    ll* fenwick = (i++ & 1 ? odd : even);
    ll ret = 0;
    for (i /= 2; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
ll query(int l, int r) {
    int Ol = l + !(l & 1), Or = r - !(r & 1);
    int El = l + (l & 1), Er = r - (r & 1);
    
    ll O = (Ol <= Or ? read(Or) - read(Ol - 2) : 0);
    ll E = (El <= Er ? read(Er) - read(El - 2) : 0);
    ll ret = O - E;
    return ret > 0 ? ret : -ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int Q; cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        int v; cin >> v;
        update(i, v);
    }

    while (Q--) {
        int q, l, r; cin >> q >> l >> r;
        if (q == 1) cout << query(l, r) << '\n';
        else update(l, r);
    }
    return 0;
}