#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main()
{
    int A, B; cin >> A >> B;
    B /= A;

    for (int i = sqrt(B); i > 0;--i)
        if (B % i == 0 && gcd(B / i, i) == 1) {
            cout << i * A << ' ' << B / i * A;
            break;
        }
    return 0;
}