#include<iostream>
using namespace std;

int main()
{
    int n, a = 10;
    cin >> n;
    while (a < n) {
        int trash = n % a;
        if (trash >= a - trash)
            n = n - trash + a;
        else
            n = n - trash;
        a *= 10;
    }
    cout << n;
    return 0;
}