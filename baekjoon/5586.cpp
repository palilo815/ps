#include<iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int J = 0, I = 0;
    for (int i = 1;i < s.size() - 1; ++i) {
        if (s[i] == 'O') {
            if (s[i + 1] == 'I') {
                if (s[i - 1] == 'J') ++J;
                else if (s[i - 1] == 'I') ++I;
            }
            ++i;
        }
    }
    cout << J << '\n' << I;
    return 0;
}