#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s1, s2;
    while (cin >> s1 >> s2) {
        if (s1 == "E") break;
        int p1 = 0, p2 = 0;
        loop(i, s1.size()) {
            if (s1[i] == 'R') {
                if (s2[i] == 'S') ++p1;
                else if (s2[i] == 'P') ++p2;
            }
            else if (s1[i] == 'S') {
                if (s2[i] == 'P') ++p1;
                else if (s2[i] == 'R') ++p2;
            }
            else {
                if (s2[i] == 'R') ++p1;
                else if (s2[i] == 'S') ++p2;
            }
        }
        cout << "P1: " << p1 << '\n';
        cout << "P2: " << p2 << '\n';
    }
    return 0;
}