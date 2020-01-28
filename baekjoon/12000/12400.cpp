#include <iostream>
#include <string>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    char code[26] = { 'y', 'h', 'e', 's', 'o', 'c', 'v', 'x', 'd', 'u', 'i', 'g', 'l', 'b', 'k', 'r', 'z' , 't', 'n', 'w', 'j', 'p', 'f', 'm', 'a', 'q' };
    string s;
    int t; cin >> t; cin.ignore();
    for (int i = 1; i <= t; ++i) {
        getline(cin, s);
        cout << "Case #" << i << ": ";
        for (char c : s) {
            if (c == ' ') cout << c;
            else cout << code[c - 'a'];
        }
        cout << '\n';
    }
}