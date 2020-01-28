#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool sieve[1001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<int> prime;
    for (int i = 2; i < 1001; ++i)
        if (!sieve[i]) {
            prime.push_back(i);
            for (int j = i * i; j < 1001; j += i)
                sieve[j] = true;
        }
    int len = prime.size();
    int T, k; cin >> T;
    while (T--) {
        bool flag = false;
        cin >> k;
        loop(a, len) for (int b = a;b < len;++b) for (int c = b;c < len;++c)
            if (prime[a] + prime[b] + prime[c] == k) {
                cout << prime[a] << ' ' << prime[b] << ' ' << prime[c] << '\n';
                flag = true;
                goto OUT;
            }
    OUT:;
        if (!flag) cout << "0\n";
    }
    return 0;
}