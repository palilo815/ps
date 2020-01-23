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

    int M; cin >> N >> M;
    // origin : 저장된 숫자
    vector<ll> origin(N), fenwick(N + 1);
    loop(i, N) {
        cin >> origin[i];
        update(fenwick, i + 1, origin[i]);
    }
    while (M--) {
        ll x, y, a, b;
        cin >> x >> y >> a >> b;
        if (x > y) swap(x, y); // 아니 왜 x > y인 테케가 있는거죠;;;
        cout << read(fenwick, y) - read(fenwick, x - 1) << '\n';
        // 저장된 숫자를 b로 바꾸고, 그 차이만큼 fenwick tree를 update
        ll gap = b - origin[a - 1];
        origin[a - 1] = b;
        update(fenwick, a, gap);
    }
    return 0;
}