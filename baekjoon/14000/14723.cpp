#include <iostream>
using namespace std;

int main()
{
    int n, dia = 1;
    cin >> n;
    while (n > dia) n -= dia++;
    cout << dia + 1 - n << ' ' << n;
    return 0;
}