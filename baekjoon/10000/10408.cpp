#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    string s; cin >> s;
    double ans = 0, count = 0;
    int len = s.size();
    loop(i, len) {
        ++count;
        if (s[i] == '1' && s[i + 1] == '0') {
            ans += 10;
            ++i;
        }
        else ans += s[i] - '0';
    }
    printf("%.2lf", ans / count);
    return 0;
}