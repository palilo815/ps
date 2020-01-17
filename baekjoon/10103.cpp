#include <iostream>
using namespace std;

int main()
{
    int A = 100, B = 100;
    int n; cin >> n;
    while (n--) {
        int a, b; cin >> a >> b;
        if (a < b) A -= b;
        if (a > b) B -= a;
    }
    cout << A << '\n' << B;
    return 0;
}