#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string A, B; cin >> A >> B;
    int x, y;
    loop(i,A.size()) loop(j,B.size())
        if (A[i] == B[j]) {
            x = i, y = j;
            goto OUT;
        }
OUT:
    loop(i, B.size()) {
        if (i == y) cout << A;
        else {
            loop(j, A.size()) {
                if (j == x)
                    cout << B[i];
                else
                    cout << '.';
            }
        }
        cout << '\n';
    }
    return 0;
}