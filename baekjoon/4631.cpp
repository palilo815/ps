#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int St = 0, n;
    string s[15];
    while (cin >> n) {
        if (n == 0) break;
        loop(i, n) cin >> s[i];
        cout << "SET " << ++St << '\n';
        for (int i = 0; i < n; i += 2)
            cout << s[i] << '\n';
        for (int i = n - 1 - (n % 2); i >= 0; i -= 2)
            cout << s[i] << '\n';
    }
    return 0;
}