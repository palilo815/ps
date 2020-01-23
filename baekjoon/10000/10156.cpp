#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    a *= b;
    a -= c;
    if (a < 0) a = 0;
    cout << a;
    return 0;
}