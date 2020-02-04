#include <iostream>
using namespace std;

int main()
{
    char op; string s;
    cin >> op >> s;
    int len = s.size();

    if (op == 'E') {
        char prev = s[0];
        int num = 1;
        for (int i = 1; i < len; ++i) {
            if (s[i] == prev) ++num;
            else {
                cout << prev << num;
                prev = s[i], num = 1;
            }
        }
        cout << prev << num;
    }
    else
        for (int i = 0; i < len; i += 2) {
            char c = s[i], n = s[i + 1];
            cout << string(n - '0', c);
        }
    return 0;
}