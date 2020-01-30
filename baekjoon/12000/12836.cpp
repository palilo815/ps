#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long
using namespace std;

int N;
ll read(vector<ll>& tree, int idx)
{
    ll sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
void update(vector<ll>& tree, int idx, ll val)
{
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
    vector<ll> origin(N), fenwick(N + 1);

    while (M--) {
        int op, a, b;
        cin >> op >> a >> b;
        // op == 1 : 가계부에 b를 추가,
        // (변경이 아니라 추가다!)
        if (op == 1) {
            origin[a - 1] += b;
            update(fenwick, a, b);
        }
        // op == 2 : 출력
        else
            cout << read(fenwick, b) - read(fenwick, a - 1) << '\n';
    }
    return 0;
}