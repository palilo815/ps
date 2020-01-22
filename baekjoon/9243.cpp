#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;
    bool f;
    if (n % 2) {
        f = true;
        int L = s1.size();
        loop(i, L)
            if (s1[i] == s2[i]) {
                f = false;
                break;
            }
    }
    else {
        if (s1 == s2) f = true;
        else f = false;
    }
    cout << "Deletion ";
    if (f) cout << "succeeded";
    else cout << "failed";
    return 0;
}