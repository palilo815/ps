#include<iostream>
using namespace std;

int main()
{
    int a, n = 5, sum = 0;
    while (n--) {
        cin >> a;
        if (a < 40) a = 40;
        sum += a;
    }
    cout << sum / 5;
    return 0;
}