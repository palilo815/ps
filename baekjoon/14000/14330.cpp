#include <iostream>
using namespace std;

const int mod = 1000000007;

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        string s; cin >> s;
        long long ans = 1;
        int L = s.size();
        if (L != 1) {
            if (s[0] != s[1]) ans *= 2;
            if (s[L - 1] != s[L - 2]) ans *= 2;
            for (int i = 1; i < L - 1; ++i) {
                int cnt = 1;
                if (s[i - 1] != s[i]) ++cnt;
                if (s[i + 1] != s[i] && s[i + 1] != s[i - 1]) ++cnt;
                ans = ans * cnt % mod;
            }
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}