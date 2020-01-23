#include<iostream>
using namespace std;

int main()
{
    int N, a, sum = 1;
    cin >> N;
    while (N-- > 0) {
        cin >> a;
        sum--;
        sum += a;
    }
    cout << sum;
    return 0;
}