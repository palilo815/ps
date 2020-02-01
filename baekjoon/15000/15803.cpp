#include<iostream>
using namespace std;

int main()
{
    int x[3], y[3];
    for (int i = 0; i < 3; i++)
        cin >> x[i] >> y[i];
    x[1] -= x[0], y[1] -= y[0];
    x[2] -= x[0], y[2] -= y[0];
    if (x[1] * y[2] == x[2] * y[1]) cout << "WHERE IS MY CHICKEN?";
    else cout << "WINNER WINNER CHICKEN DINNER!";
    return 0;
}