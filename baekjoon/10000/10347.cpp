#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

char arr[28];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 26) arr[i] = 'A' + i;
    arr[26] = '_', arr[27] = '.';

    int n; string s;
    while (1) {
        cin >> n;
        if (n == 0) break;
        cin >> s;
        reverse(s.begin(), s.end());
        int ind;
        loop(i, s.size()) {
            char c = s[i];
            if (c == '_') ind = 26;
            else if (c == '.') ind = 27;
            else ind = c - 'A';
            cout << arr[(ind + n) % 28];
        }
        cout << '\n';
    }
    return 0;
}