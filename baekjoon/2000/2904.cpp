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
        // op == 1 : a번 숫자를 b로 update
        if (op) {
            ll gap = b - origin[a - 1];
            origin[a - 1] = b;
            update(fenwick, a, gap);
        }
        // op == 0 : [a,b]합
        else {
            // 역방향을 구하는 입력도 주어짐
            if (a > b) swap(a, b);
            cout << read(fenwick, b) - read(fenwick, a - 1) << '\n';
        }
    }
    return 0;
}