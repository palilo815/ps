#include <iostream>
#include <string>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char arr[5] = { 'a','e','i','o','u' };
bool moum(char c)
{
    loop(i, 5)
        if (arr[i] == c)
            return true;
    return false;
}
bool has_moum(string pw)
{
    for (char c : pw)
        if (moum(c))
            return true;
    return false;
}
bool no_3_times(string pw)
{
    int cnt = 0;
    loop(i, pw.size() - 1) {
        if (moum(pw[i]) == moum(pw[i + 1])) {
            if (++cnt == 2)
                return false;
        }
        else
            cnt = 0;
    }
    return true;
}

bool no_same_char(string pw)
{
    loop(i, pw.size() - 1)
        if (pw[i] == pw[i + 1] && pw[i] != 'e' && pw[i] != 'o')
            return false;
    return true;
}

int main()
{
    string pw;
    while (1) {
        cin >> pw;
        if (pw == "end") break;
        cout << '<' << pw << "> is ";
        if (has_moum(pw) && no_3_times(pw) && no_same_char(pw))
            cout << "acceptable.\n";
        else
            cout << "not acceptable.\n";
    }
    return 0;
}