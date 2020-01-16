#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> ans;
    
    loop(i, n + 1) {
        vector<int> tmp;
        // 첫 번째 수 n, 두 번째 수 i
        tmp.push_back(n), tmp.push_back(i);
        int S = 2; // 만든 수열의 길이
        while (1) {
            int next = tmp[S - 2] - tmp[S - 1];
            if (next < 0) break;
            tmp.push_back(next);
            ++S;
        }
        if (S > ans.size()) ans = tmp;
    }
    cout << ans.size() << '\n';
    for (int x : ans)
        cout << x << ' ';
    return 0;
}