#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        cin >> s;
        if (s == "#") break;
        int a = 0, b = 0, sumA = 0, sumB = 0, len = s.size();
        loop(i, len) {
            if (s[i] == 'A') ++a;
            else ++b;

            if (a >= 4 && a - b >= 2) a = b = 0, ++sumA;
            if (b >= 4 && b - a >= 2) a = b = 0, ++sumB;
        }
        cout << "A " << sumA << " B " << sumB << '\n';
    }
    return 0;
}