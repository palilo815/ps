#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char arr[100][100];
int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n;
    cin >> t;
    string s;
    while (t--) {
        cin >> s;
        n = sqrt(s.size());
        int pos = 0;
        loop(j, n) loop(i, n)
            arr[n - 1 - i][j] = s[pos++];
        loop(i, n) loop(j, n)
            cout << arr[i][j];
        cout << '\n';
    }
    return 0;
}