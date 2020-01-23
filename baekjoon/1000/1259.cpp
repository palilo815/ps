#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string a, b;
    while (cin >> a) {
        if (a == "0") break;
        b = a;
        reverse(a.begin(), a.end());
        if (a == b) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}