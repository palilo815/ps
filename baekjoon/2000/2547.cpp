#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll T; cin >> T;
    while (T--) {
        int N; cin >> N;
        ll sum = 0;
        loop(i, N) {
            ll x; cin >> x;
            sum += x;
            sum %= N;
        }
        if (sum % N) cout << "NO";
        else cout << "YES";
        cout << '\n';
    }
    return 0;
}