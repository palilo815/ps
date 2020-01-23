#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int T; cin >> T;
    while (T-- > 0) {
        string s1, s2;
        cin >> s1 >> s2;
        int ans = 0;
        loop(i, s1.size())
            if (s1[i] != s2[i]) ++ans;
        printf("Hamming distance is %d.\n", ans);
    }
    return 0;
}