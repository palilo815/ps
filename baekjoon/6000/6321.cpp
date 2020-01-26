#include <iostream>
#include <string>
using namespace std;

int main()
{
    int T; cin >> T;
    string s;
    for (int i = 1;i <= T;++i) {
        cin >> s;
        cout << "String #" << i << '\n';
        for (char c : s) {
            if (c == 'Z') cout << 'A';
            else cout << ++c;
        }
        cout << '\n' << '\n';
    }
    return 0;
}