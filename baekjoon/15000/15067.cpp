#include <bits/stdc++.h>
using namespace std;

const int mx = 1e4;

bool sieve[mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i < mx; ++i)
        if (!sieve[i])
            for (int j = i * i; j < mx; j += i)
                sieve[j] = true;

    char s[4];
    int N;
    for (;;) {
        cin >> s >> N;
        if (!strcmp(s, "END")) break;

        auto it = find(sieve + N, sieve + mx, 0);
        if (it == sieve + mx) {
            it = sieve + 2;
            if (s[2] == 'Z') {
                s[2] = 'A';
                s[1] == 'Z' ? (s[1] = 'A', ++s[0]) : ++s[1];
            }
            else ++s[2];
        }
        cout << s << ' ' << setfill('0') << setw(4) << it - sieve << '\n';
    }
    return 0;
}