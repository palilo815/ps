#include<iostream>
using namespace std;

int main()
{
    int n = 64, x, count = 0;
    cin >> x;
    while (x > 0) {
        if (x >= n) {
            x -= n;
            count++;
        }
        n /= 2;
    }
    cout << count;
    return 0;
}