#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s1, s2;
    int A[26], B[26], Case = 0;
    while (cin >> s1 >> s2) {
        if (s1 == "END") break;
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));

        int L1 = s1.length(), L2 = s2.length();
        loop(i, L1) ++A[s1[i] - 'a'];
        loop(i, L2) ++B[s2[i] - 'a'];

        cout << "Case " << ++Case << ": ";
        loop(i, 26) {
            if (A[i] != B[i]) {
                cout << "different\n";
                break;
            }
            if (i == 25) cout << "same\n";
        }
    }
    return 0;
}