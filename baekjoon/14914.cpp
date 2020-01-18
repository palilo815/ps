#include <iostream>
using namespace std;

int GCD(int a, int b)
{
    if (a == 0) return b;
    return GCD(b % a, a);
}

int main()
{
    int apple, banana; cin >> apple >> banana;
    int gcd = GCD(apple, banana);
    for (int i = 1;i <= gcd;++i)
        if (gcd % i == 0)
            cout << i << ' ' << apple / i << ' ' << banana / i << '\n';
    return 0;
}