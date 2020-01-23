#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<=n;++i)

bool MySort(string s1, string s2)
{
    if (s1.length() != s2.length()) return s1.length() < s2.length();
    int n1 = 0, n2 = 0;
    loop(i, s1.length())
        if (s1[i] <= '9') n1 += s1[i] - '0';
    loop(i, s2.length())
        if (s2[i] <= '9') n2 += s2[i] - '0';
    if (n1 != n2) return n1 < n2;
    return s1 < s2;
}

string guitar[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> guitar[i];
    sort(guitar, guitar + n, MySort);
    loop(i, n) cout << guitar[i] << '\n';
    return 0;
}