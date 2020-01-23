#include<iostream>
using namespace std;

int main()
{
    int a, b, c, d, sum;
    cin >> a >> b >> c >> d;
    sum = a + b + c + d;
    cout << sum / 60 << '\n' << sum % 60;
    return 0;
}