#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, n;
    char c;
    cin >> T;
    while (T--) {
        cin >> n >> c;
        if (c == 'C') {
            vector<int> ans;
            while (n--) {
                char x; cin >> x;
                ans.push_back(x - 'A' + 1);
            }
            for (int x : ans) cout << x << ' ';
        }
        else {
            vector<char> ans;
            while (n--) {
                int x; cin >> x;
                ans.push_back(x + 'A' - 1);
            }
            for (char x : ans) cout << x << ' ';
        }
        cout << '\n';
    }
    return 0;
}