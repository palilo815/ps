#include<iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b, c;
    while (1) {
        cin >> a >> b >> c;
        if (a == 0 && b == 0) break;
        if (b - a == c - b && b - a != 0)
            cout << "AP " << c + b - a << '\n';
        else
            cout << "GP " << c * b / a << '\n';
    }
    return 0;
}