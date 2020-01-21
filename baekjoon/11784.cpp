#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int Hex(char a, char b) {
    int A, B;
    if (a < 'A') A = a - '0';
    else A = a - 'A' + 10;
    if (b < 'A') B = b - '0';
    else B = b - 'A' + 10;
    return 16 * A + B;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        int len = s.size();
        for (int i = 0; i < len;i += 2) {
            char c = Hex(s[i], s[i + 1]);
            cout << c;
        }
        cout << '\n';
    }
    return 0;
}