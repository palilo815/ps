#include <iostream>
using namespace std;
const int max_prime = 7368787;
// 500,000th prime : 7,368,787

bool sieve[max_prime + 1];
int main()
{
    int K; cin >> K;
    int cnt = 0;
    for (long long i = 2; i <= max_prime; ++i)
        if (!sieve[i]) {
            if (++cnt == K) {
                cout << i;
                break;
            }
            for (long long j = i * i; j <= max_prime; j += i)
                sieve[j] = true;
        }
    return 0;
}