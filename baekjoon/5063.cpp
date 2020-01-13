#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, ori, ad, ad_p;
    cin >> T;
    while (T-- > 0) {
        cin >> ori >> ad >> ad_p;
        if (ori < ad - ad_p)
            cout << "advertise" << endl;
        else if (ori == ad - ad_p)
            cout << "does not matter" << endl;
        else
            cout << "do not advertise" << endl;
    }
    return 0;
}