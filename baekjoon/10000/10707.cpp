#include<iostream>
using namespace std;

int main()
{
    int X, Y, use;
    int x_per, y_base, y_limit, y_per;
    cin >> x_per >> y_base >> y_limit >> y_per >> use;
    X = x_per * use;
    Y = (use < y_limit) ? y_base : y_base + (use - y_limit) * y_per;
    int min = (X < Y) ? X : Y;
    cout << min;
    return 0;
}