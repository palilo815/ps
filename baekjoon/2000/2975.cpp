#include <iostream>
using namespace std;

int main()
{
    int B, A;
    char c;
    while (1) {
        cin >> B >> c >> A;
        if (B == 0 && c == 'W' && A == 0) break;
        if (c == 'D') cout << B + A << '\n';
        else {
            B -= A;
            if (B < -200) cout << "Not allowed\n";
            else cout << B << '\n';
        }
    }
    return 0;
}