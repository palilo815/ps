#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int A[26], B[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    string s1, s2;
    while (t--) {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        cin >> s1 >> s2;
        for (char c : s1) ++A[c - 'a'];
        for (char c : s2) ++B[c - 'a'];
        cout << s1 << " & " << s2 << " are ";

        bool flag = false;
        loop(i, 26)
            if (A[i] != B[i]) {
                flag = true;
                break;
            }
        if (flag) cout << "NOT ";
        cout << "anagrams.\n";
    }
    return 0;
}