#include <iostream>
#include <string>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int happy = 0, sad = 0;
    getline(cin, s);
    for (int i = 0; i < s.size() - 2;++i)
        if (s[i] == ':')
            if (s[i + 1] == '-') {
                if (s[i + 2] == ')') ++happy;
                else if (s[i + 2] == '(') ++sad;
            }

    if (happy == sad) {
        if (happy == 0) cout << "none";
        else cout << "unsure";
    }
    else if (happy > sad) cout << "happy";
    else cout << "sad";
    return 0;
}