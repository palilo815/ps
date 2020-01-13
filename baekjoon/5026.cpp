#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    string s;
    while (t--) {
        cin >> s;
        if (s[0] == 'P') {
            cout << "skipped\n";
            continue;
        }
        // a : + 왼쪽에 있는 수
        // b : + 오른쪽
        // ex) 10 + 100 -> a=10, b=100
        int a = 0, b = 0, pos, L = s.length();
        for (pos = 0; s[pos] != '+'; ++pos) {
            a *= 10;
            a += s[pos] - '0';
        }
        for (pos = pos + 1;pos < L; ++pos) {
            b *= 10;
            b += s[pos] - '0';
        }
        cout << a + b << '\n';
    }
    return 0;
}