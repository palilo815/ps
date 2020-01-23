#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    while (getline(cin, s)) {
        if (s == "EOI") break;
        int L = s.length();
        bool f = false;
        loop(i, L) {
            if (s[i] == 'n' || s[i] == 'N') {
                if (s[i + 1] == 'e' || s[i + 1] == 'E') {
                    if (s[i + 2] == 'm' || s[i + 2] == 'M') {
                        if (s[i + 3] == 'o' || s[i + 3] == 'O') {
                            f = true;
                            break;
                        }
                        i += 2; // 현재 글자는 NEM?
                                // 다음 탐색은 ?부터 해야한다.
                    }
                    ++i;    // 현재 글자는 NE?
                            // 다음 탐색은 ?부터 해야한다.
                }
            }
        }
        if (f) cout << "Found\n";
        else cout << "Missing\n";
    }
    return 0;
}