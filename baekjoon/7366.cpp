#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int T, n; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> n;
        int ans = 0;
        while (n--) {
            cin >> s;
            if (s == "sheep") ++ans;
        }
        cout << "Case " << t << ": This list contains " << ans << " sheep.\n\n";
    }
    return 0;
}