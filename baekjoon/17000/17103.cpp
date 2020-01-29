#include <iostream>
using namespace std;
const int max_N = 1000000;

bool sieve[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    for (int i = 2;i < max_N;++i)
        if (!sieve[i])
            for (int j = 3 * i;j < max_N;j += 2 * i)
                sieve[j] = true;

    int T; cin >> T;
    int n;
    while (T--) {
        int ans = 0;
        cin >> n;
        for (int i = 3;i <= n / 2;i += 2)
            if (!sieve[i] && !sieve[n - i])
                ++ans;
        cout << ans << '\n';
    }
    return 0;
}