#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string tmp, s;
    while (1) {
        cin >> tmp;	// START 입력
        if (tmp == "ENDOFINPUT") break;
        cin.ignore();
        getline(cin, s);
        loop(i, s.length()) {
            char c = s[i];
            if (c >= 'A' && c <= 'Z') {
                c -= 5;
                if (c < 'A') c += 26;
            }
            cout << c;
        }
        cout << '\n';
        cin >> tmp;	// END 입력
    }
    return 0;
}