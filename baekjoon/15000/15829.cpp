#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int L;
    string s;
    cin >> L >> s;
    ll MOD = 1234567891, Hash = 0;
    loop(i, L) {
        ll tmp = 1;
        loop(j, i) {
            tmp *= 31;
            tmp %= MOD;
        }
        Hash += (s[i] - 'a' + 1) * tmp;
        Hash %= MOD;
    }
    cout << Hash;
    return 0;
}