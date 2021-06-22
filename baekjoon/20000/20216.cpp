#include <bits/stdc++.h>
using namespace std;

int main() {
    for (string s;;) {
        getline(cin, s);
        if (s.back() == '.')
            cout << "*Nod*" << endl;
        else if (s.back() == '?')
            cout << "Quack!" << endl;
        else
            break;
    }
}