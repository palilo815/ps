#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s1, s2;
    cin >> s1 >> s2;
    long long sum1 = 0, sum2 = 0;
    loop(i, s1.size()) sum1 += s1[i] - '0';
    loop(i, s2.size()) sum2 += s2[i] - '0';
    cout << sum1 * sum2;
    return 0;
}