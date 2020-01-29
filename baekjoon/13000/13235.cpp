#include <iostream>
using namespace std;

int main()
{
    string s; cin >> s;
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) {
            cout << "false";
            return 0;
        }
        ++l, --r;
    }
    cout << "true";
    return 0;
}