#include <iostream>
using namespace std;

int main()
{
    char c; cin >> c;
    if (c == 'F') cout << "0.0";
    else {
        int a, b;
        a = -c + 69;
        cin >> c;
        if (c == '+') b = 3;
        else if (c == '0') b = 0;
        else --a, b = 7;
        cout << a << '.' << b;
    }
    return 0;
}