#include <iostream>
using namespace std;

string s;
bool accept() {
    bool moum = false;
    int len = s.size(), cnt = 0;
    s += '?';
    for (int i = 0; i < len; ++i) switch (s[i]) {
    case 'a':
    case 'i':
    case 'u':
        if (s[i + 1] == s[i]) return false;
    case 'e':
    case 'o':
        moum = true;
        if (cnt > 0) {
            if (++cnt >= 3) return false;
        }
        else cnt = 1;
        break;
    default:
        if (s[i + 1] == s[i]) return false;
        if (cnt < 0) {
            if (--cnt <= -3) return false;
        }
        else cnt = -1;
    }
    return moum;
}
int main() {
    while (1) {
        cin >> s;
        if (s == "end") break;
        cout << '<' << s << "> is ";
        if (!accept()) cout << "not ";
        cout << "acceptable.\n";
    }
    return 0;
}