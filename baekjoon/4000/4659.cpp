#include <iostream>
using namespace std;

bool accept(string& s) {
    bool moum = false;
    int len = s.size(), cnt = 0;
    for (int i = 0; i < len; ++i) switch (s[i]) {
    case 'a':
    case 'i':
    case 'u':
        if (i + 1 < len && s[i + 1] == s[i])
            return false;
    case 'e':
    case 'o':
        moum = true;
        if (cnt > 0) {
            if (++cnt >= 3) return false;
        }
        else cnt = 1;
        break;
    default:
        if (i + 1 < len && s[i + 1] == s[i])
            return false;
        if (cnt < 0) {
            if (--cnt <= -3) return false;
        }
        else cnt = -1;
    }
    return moum;
}
int main() {
    string pw;
    while (1) {
        cin >> pw;
        if (pw == "end") break;
        cout << '<' << pw << "> is ";
        if (!accept(pw)) cout << "not ";
        cout << "acceptable.\n";
    }
    return 0;
}