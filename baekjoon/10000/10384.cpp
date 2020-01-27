#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int arr[26];
    int T; cin >> T; cin.ignore();
    for (int t = 1; t <= T; ++t) {
        memset(arr, 0, sizeof(arr));
        getline(cin, s);
        int Len = s.size();
        loop(i, Len) {
            char c = s[i];
            if (c >= 'a' && c <= 'z') ++arr[c - 'a'];
            else if (c >= 'A' && c <= 'Z') ++arr[c - 'A'];
        }
        int ans = 3;
        loop(i, 26)
            ans = min(ans, arr[i]);
        cout << "Case " << t << ": ";
        if (ans == 3) cout << "Triple pangram!!!\n";
        else if (ans == 2) cout << "Double pangram!!\n";
        else if (ans == 1) cout << "Pangram!\n";
        else cout << "Not a pangram\n";
    }
    return 0;
}