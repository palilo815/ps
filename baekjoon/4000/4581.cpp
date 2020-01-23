#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (cin >> s) {
        if (s == "#") break;
        int Y = 0, N = 0, A = 0;
        loop(i, s.size()) {
            if (s[i] == 'A') ++A;
            else if (s[i] == 'Y') ++Y;
            else if (s[i] == 'N') ++N;
        }
        if (2 * A >= s.size()) cout << "need quorum\n";
        else if (Y > N) cout << "yes\n";
        else if (Y < N) cout << "no\n";
        else cout << "tie\n";
    }
    return 0;
}