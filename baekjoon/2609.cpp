#include<iostream>
#include<algorithm>
using namespace std;

int Euclid(int m, int n)
{
    while (1) {
        int r = m % n;
        if (r == 0) return n;
        m = n, n = r;
    }
}

int main()
{
    int a, b;
    cin >> a >> b;
    int gcd = Euclid(max(a, b), min(a, b));
    cout << gcd << '\n'
        << a * b / gcd;
    return 0;
}