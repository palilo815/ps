#include <iostream>
using namespace std;

int main()
{
    int len, scr = 0;
    string s;
    cin >> len >> s;
    for (int i = 0;i < len;++i)
        scr += s[i] - 'A' + 1;
    cout << scr;
    return 0;
}