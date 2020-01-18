#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        if (n == 0) break;
        vector<int> ans;
        int prev = 0;
        while (n--) {
            int x; cin >> x;
            if (x == prev) continue;
            prev = x;
            ans.push_back(x);
        }
        for (int x : ans) cout << x << ' ';
        cout << "$\n";
    }
    return 0;
}