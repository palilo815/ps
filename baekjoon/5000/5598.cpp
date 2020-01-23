#include <iostream>
using namespace std;

int main()
{
    string s; cin >> s;
    for (char c : s) {
        c -= 3;
        if (c < 'A') c += 26;
        cout << c;
    }
    return 0;
}