#include<iostream>
using namespace std;

int main()
{
    int ans, n;
    char c;
    cin >> ans;
    while (1) {
        cin >> c;
        if (c == '=') break;
        cin >> n;
        if (c == '+') ans += n;
        else if (c == '-') ans -= n;
        else if (c == '*') ans *= n;
        else ans /= n;
    }
    cout << ans;
    return 0;
}