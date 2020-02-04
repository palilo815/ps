#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    bool T[4] = {};
    int n; cin >> n;
    int ans1 = 6 - n, ans2 = 0;
    while (n--) {
        char c; cin >> c;
        if (c >= 'a' && c <= 'z') T[0] = true;
        else if (c >= 'A' && c <= 'Z') T[1] = true;
        else if (c >= '0' && c <= '9') T[2] = true;
        else T[3] = true;
    }
    loop(i, 4)
        if (!T[i])++ans2;
    cout << max(ans1, ans2);
    return 0;
}