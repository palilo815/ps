#include <bits/stdc++.h>
using namespace std;
const size_t MAX = 1000000001;

size_t i, j, k;
bitset<MAX> cnt;
bitset<MAX> sieve;

void Eratos() {
    for (i = 2; i * i < MAX; ++i) if (!sieve[i])
        for (j = i * i; j < MAX; j += i)
            sieve[j] = 1;
}
void count_prime() {
    for (i = 2; i < MAX; ++i) if (!sieve[i])
        for (j = i; j < MAX; j *= i)
            for (k = j; k < MAX; k += j)
                cnt[k] = !cnt[k];
}
void generate() {
    int odd = 1, even = 0;
    bool prv = true;

    for (i = 2; i < MAX; ++i) {
        cnt[i] ? ++even : ++odd;
        bool cur = (even >= odd);

        if (cur != prv) {
            cout << i << ' ';
            prv = cur;
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    freopen("out.txt", "w", stdout);

    Eratos();
    count_prime();
    generate();

    return 0;
}