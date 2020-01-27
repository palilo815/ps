#include <iostream>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n;
    string s1, s2;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> n >> s1 >> s2;
        int cnt = 0;
        for (int j = 0; j < n; ++j)
            if (s1[j] != s2[j]) ++cnt;
        cout << "Case " << i << ": " << cnt << '\n';
    }
    return 0;
}