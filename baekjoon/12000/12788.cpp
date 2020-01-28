#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 1000;

int pen[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m, k; cin >> n >> m >> k;
    int need = m * k, ans = 0;
    loop(i, n) cin >> pen[i];
    sort(pen, pen + n, greater<int>());
    loop(i, n) {
        need -= pen[i];
        ++ans;
        if (need <= 0) break;
    }
    if (need > 0) cout << "STRESS";
    else cout << ans;
    return 0;
}