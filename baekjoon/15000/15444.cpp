#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char arr[5][16] = {
"***************",
"*.**.**..*.**..",
"*******..*.****",
"*.**.**..*.**..",
"*.*************" };

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    string s;
    cin >> N >> s;
    loop(j, 5) {
        loop(i, N) {
            int pos = (s[i] - 'A') * 3;
            loop(k, 3) cout << arr[j][pos + k];
        }
        cout << '\n';
    }
    return 0;
}