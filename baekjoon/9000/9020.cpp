#include <bits/stdc++.h>
using namespace std;

bool sieve[10000];
int main()
{
    vector<int> prime;
    for (int i = 2;i < 10000;++i)
        if (!sieve[i]) {
            prime.push_back(i);
            for (int j = i * i;j < 10000;j += i)
                sieve[j] = true;
        }
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        auto it = lower_bound(prime.begin(), prime.end(), n / 2);
        while (1) {
            if (binary_search(it, prime.end(), n - *it)) {
                cout << *it << ' ' << n - *it << '\n';
                break;
            }
            --it;
        }
    }
    return 0;
}