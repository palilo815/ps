#include<iostream>
using namespace std;

int main()
{
    long sum;
    int n = 0;
    cin >> sum;
    for (long i = 1; i <= sum;i++) {
        sum -= i;
        n++;
    }
    cout << n;
    return 0;
}