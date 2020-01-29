#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int a = 0, b = 0, len = s.size(), A = 0, B = 0;
    loop(i, len) {
        if (s[i] == 'A') ++a;
        else ++b;
        if (a == 21 || b== 21) {
            cout << a << '-' << b << '\n';
            if (a == 21) ++A;
            else ++B;
            a = 0, b = 0;
        }
    }
    if (A > B) cout << 'A';
    else cout << 'B';
    return 0;
}