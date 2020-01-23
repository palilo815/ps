#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    string A, B;
    char op;
    cin >> A >> op >> B;
    if (op == '*')
        cout << A.append(B.size() - 1, '0');
    else {
        if (A == B)
            cout << A.replace(0, 1, "2");
        else {
            string L = (A.size() > B.size()) ? A : B; // large str
            string S = (A.size() > B.size()) ? B : A; // small str
            cout << L.replace(L.size() - S.size(), 1, "1");
        }
    }
    return 0;
}
