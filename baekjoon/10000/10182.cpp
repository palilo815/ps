#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    string s;
    char c;
    double n;
    int t; cin >> t;
    while (t--) {
        cin >> s >> c >> n;
        if (s == "H") printf("%.2lf\n", -log10(n));
        else printf("%.2lf\n", 14 + log10(n));
    }
    return 0;
}