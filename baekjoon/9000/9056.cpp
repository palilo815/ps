#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    bool arr[2][26];
    int T; cin >> T;
    while (T--) {
        memset(arr, 0, sizeof(arr));
        string bank, word;
        cin >> bank >> word;
        loop(i, bank.size())
            arr[0][bank[i] - 'A'] = true;
        loop(i, word.size())
            arr[1][word[i] - 'A'] = true;

        bool flag = true;
        loop(i, 26)
            if (arr[0][i] != arr[1][i])
                flag = false;
        if (flag) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}