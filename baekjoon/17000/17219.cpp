#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<string,string>
using namespace std;
const int max_N = 100000;

P pw[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);
    
    int N, Q; cin >> N >> Q;
    loop(i, N) cin >> pw[i].first >> pw[i].second;
    sort(pw, pw + N);

    P site;
    while (Q--) {
        cin >> site.first;
        auto it = lower_bound(pw, pw + N, site);
        cout << it->second << '\n';
    }
    return 0;
}