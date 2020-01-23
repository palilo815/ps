#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        if (next_permutation(s.begin(), s.end()))
            cout << s << '\n';
        else
            cout << "BIGGEST\n";
    }
    return 0;
}