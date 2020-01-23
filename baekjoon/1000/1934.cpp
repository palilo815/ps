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
    int t, a, b;
    cin >> t;
    while (t-- > 0) {
        cin >> a >> b;
        int gcd = Euclid(max(a, b), min(a, b));
        cout << a * b / gcd << '\n';
    }
    return 0;
}