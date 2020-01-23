#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int len; cin >> len;
        vector<bool> check(4);
        loop(i, len) {
            char c; cin >> c;
            if (c >= 'a' && c <= 'z') check[0] = true;
            else if (c >= 'A' && c <= 'Z') check[1] = true;
            else if (c >= '0' && c <= '9') check[2] = true;
            else check[3] = true;
        }
        if (len < 12) { cout << "invalid\n"; continue; }
        loop(i, 4) {
            if (!check[i]) {
                cout << "invalid\n";
                break;
            }
            if (i == 3) cout << "valid\n";
        }
    }
    return 0;
}