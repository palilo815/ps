#include <iostream>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int gate[100000];
bool pass(ll time, int N, int M)
{
    ll num = 0;
    loop(i, N)
        num += time / (ll)gate[i];
    if (num < (ll)M) return false;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> gate[i];
    ll s = 1, e = 1000000000000000000, ans;
    while (s <= e) {
        ll m = s + (e - s) / 2;
        if (pass(m, N, M)) {
            ans = m;
            e = m - 1;
        }
        else s = m + 1;
    }
    cout << ans;
    return 0;
}