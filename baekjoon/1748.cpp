#include<iostream>
using namespace std;

int main()
{
    long N, i, sum = 0;
    cin >> N;
    for (i = 1;i <= N;i *= 10)
        sum += N - i + 1;
    cout << sum;
    return 0;
}