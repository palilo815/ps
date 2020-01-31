#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    string F = ":fan:", s;
    cin >> s;
    loop(i, 3) {
        loop(j, 3) {
            if (i == 1 && j == 1) cout << ':' << s << ':';
            else cout << F;
        }
        cout << '\n';
    }
    return 0;
}