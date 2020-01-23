#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n; cin >> t;
    while (t--) {
        char arr[26];
        loop(i, 26) arr[i] = 'a' + i;
        cin >> n;
        while (n--) {
            int x; cin >> x;
            cout << arr[x];
            char tmp = arr[x];
            for (int i = x; i > 0; --i)
                arr[i] = arr[i - 1];
            arr[0] = tmp;
        }
        cout << '\n';
    }
    return 0;
}