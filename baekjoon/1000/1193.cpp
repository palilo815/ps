#include<iostream>
using namespace std;

int main()
{
    int x, i = 1;
    cin >> x;
    while (x > i)
        x -= i++;
    if (i % 2 == 0)
        cout << x << '/' << i - x + 1;
    else
        cout << i - x + 1 << '/' << x;
    return 0;
}