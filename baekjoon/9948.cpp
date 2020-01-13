#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

string Month[12] = { "January", "February", "March", "April", "May","June","July","August","September","October","November","December" };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int d, m;
    while (cin >> d >> s) {
        if (d == 0) break;
        loop(i, 12)
            if (s == Month[i]) m = i + 1;
        if (m == 2 && d == 29) cout << "Unlucky\n";
        else if (m < 8 || (m == 8 && d < 4)) cout << "Yes\n";
        else if (m == 8 && d == 4) cout << "Happy birthday\n";
        else cout << "No\n";
    }
    return 0;
}