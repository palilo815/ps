#include <bits/stdc++.h>
using namespace std;

const int max_N = 40000;
const int mod = 123456789;

bool sieve[max_N + 1];
int DP[max_N + 1];

int main() {
    int N; cin >> N;
    for (int i = 2; i * i <= N; ++i)
        if (!sieve[i])
            for (int j = i * i; j <= N; j += i)
                sieve[j] = true;
    
    DP[0] = 1;
    for (int i = 2; i <= N; ++i) if (!sieve[i]) {
        for (int j = 0; j + i <= N; ++j)
            DP[j + i] = (DP[j + i] + DP[j]) % mod;
    }
    cout << DP[N];
    return 0;
}