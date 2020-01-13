#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char arr[10] = { 'a','e','i','o','u','A','E','I','O','U' };
bool check(char a)
{
    loop(i, 10) if (a == arr[i]) return true;
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (1) {
        int n = 0;
        getline(cin, s);
        if (s == "#") break;
        loop(i, s.size()) if (check(s[i])) ++n;
        cout << n << '\n';
    }
    return 0;
}