#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    cin.ignore();

    string str1, str2;
    getline(cin, str1);
    int len = str1.length();

    while (--N) {
        getline(cin, str2);
        loop(i, len)
            if (str1[i] != str2[i])
                str1[i] = '?';
    }
    cout << str1;
    return 0;
}