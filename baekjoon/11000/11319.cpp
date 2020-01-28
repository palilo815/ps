#include <iostream>
#include <string>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char vowels[10] = { 'A','E','I','O','U','a','e','i','o','u' };
bool VOWEL(char c)
{
    loop(i, 10) if (c == vowels[i]) return true;
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int t; cin >> t; cin.ignore();
    while (t--) {
        getline(cin, s);
        int x = 0, y = 0;
        loop(i, s.size()) {
            if (s[i] == ' ') continue;
            if (VOWEL(s[i])) ++y;
            else ++x;
        }
        cout << x << ' ' << y << '\n';
    }
    return 0;
}