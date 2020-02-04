#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;

int main()
{
    string s; cin >> s;
    ll ans = 0, dig = 1;
    int len = s.size();
    loop(i, len) {
        ll num = s[len - 1 - i] - 'A' + 1;
        ans += num * dig;
        dig *= 26;
    }
    cout << ans;
    return 0;
}