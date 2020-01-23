#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, N, num;
    cin >> T;
    while (T--) {
        cin >> N;
        int psum = 0, ans = INT_MIN;
        while (N--) {
            cin >> num;
            psum = max(num, psum + num);
            ans = max(ans, psum);
        }
        cout << ans << '\n';
    }
    return 0;
}