#include <iostream>
using namespace std;

const int max_K = 1000000;

string p;
int K;
bool sieve[max_K + 1];

bool divided(int mod) {
    int ret = 0;
    for (char c : p)
        ret = (ret * 10 + (c - '0')) % mod;
    return ret == 0;
}
int main() {
    cin >> p >> K;
    for (int i = 2; i * i < K; ++i) if (!sieve[i])
        for (int j = i * i; j < K; j += i)
            sieve[j] = true;

    int ans = -1;
    for (int i = 2; i < K; ++i)
        if (!sieve[i] && divided(i)) {
            ans = i;
            break;
        }

    if (ans == -1) cout << "GOOD";
    else cout << "BAD " << ans;
    return 0;
}