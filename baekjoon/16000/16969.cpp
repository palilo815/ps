#include <iostream>
using namespace std;
typedef long long ll;
const int MOD = 1000000009;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    ll ans = 1, num;
    char prev = 'A';
    for(char c : s) {
        if (c == 'd') num = 10;
        else num = 26;
        if (prev == c) --num;
        ans = (ans * num) % MOD;
        prev = c;
    }
    cout << ans;
    return 0;
}