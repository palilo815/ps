#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int n = 7, x;
    vector<int> odd;
    while (n--) {
        cin >> x;
        if (x % 2 == 1) odd.push_back(x);
    }

    if (odd.empty()) cout << -1;
    else {
        int sum = 0, ans = 100;
        loop(i, odd.size()) {
            sum += odd[i];
            ans = min(ans, odd[i]);
        }
        cout << sum << '\n' << ans;
    }
    return 0;
}