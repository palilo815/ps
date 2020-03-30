#include <bits/stdc++.h>
using namespace std;

bool sieve[10000000];
bool used[7];

string s;
int ans, sz;

void solve(int num, int len) {
    if (!sieve[num]) ++ans;
    bool select[10] = {};
    if (len == 0) select[0] = true;

    for (int i = 0; i < sz; ++i)
        if (!used[i] && !select[s[i] - '0']) {
            used[i] = select[s[i] - '0'] = true;
            solve(num * 10 + s[i] - '0', len + 1);
            used[i] = false;
        }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i < 10000000; ++i)
        if (!sieve[i])
            for (int j = i * i; j < 10000000; j += i)
                sieve[j] = true;
    
    int T; cin >> T;
    while (T--) {
        cin >> s;
        sz = s.size(), ans = 0;

        solve(0, 0);
        cout << ans << '\n';
    }
    return 0;
}