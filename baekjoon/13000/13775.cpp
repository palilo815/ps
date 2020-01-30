#include <bits/stdc++.h>
using namespace std;

int main()
{
    int k;
    string s;
    cin >> k; cin.ignore();
    getline(cin, s);
    for (char c : s) {
        if ('a' <= c && c <= 'z') {
            c -= k;
            if (c < 'a') c += 26;
            ++k;
            if (k == 26) k = 1;
        }
        cout << c;
    }
    return 0;
}