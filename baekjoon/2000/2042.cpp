#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int N;
ll read(vector<ll>& tree, int idx) {
    ll sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void update(vector<ll>& tree, int idx, ll val) {
    while (idx <= N) {
        tree[idx] += val;
        idx += (idx & -idx);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int M, K; cin >> N >> M >> K;
    vector<ll> origin(N), fenwick(N + 1);
    loop(i, N) {
        cin >> origin[i];
        update(fenwick, i + 1, origin[i]);
    }
    M += K;
    while (M--) {
        int op;
        ll a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            ll gap = b - origin[a - 1];
            origin[a - 1] = b;
            update(fenwick, a, gap);
        }
        else
            cout << read(fenwick, b) - read(fenwick, a - 1) << '\n';
    }
    return 0;
}