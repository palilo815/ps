#include<iostream>
using namespace std;

int main()
{
    int A, B, i;
    cin >> A >> B;
    int sum = 0;
    for (i = 0; i * i < A; i++) {}
    int min = i * i;
    for (i; i * i <= B; i++)
        sum += i * i;
    if (sum == 0)
        cout << "-1";
    else
        cout << sum << endl << min;
    return 0;
}