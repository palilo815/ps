#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int A = 0, C = 0, len = s.size();

    // 첫 음이 어떤 장조의 으뜸음인지 센다
    loop(i, len)
        if (i == 0 || s[i - 1] == '|') {
            char c = s[i];
            if (c == 'A' || c == 'D' || c == 'E') ++A;
            else if (c == 'C' || c == 'F' || c == 'G') ++C;
        }

    // 만약 A, C가 똑같으면 마지막 음으로 판별
    if (A == C) {
        char Last = s[len - 1];
        if (Last == 'A' || Last == 'D' || Last == 'E') ++A;
        else if (Last == 'C' || Last == 'F' || Last == 'G') ++C;
    }

    if (A > C) cout << "A-minor";
    else cout << "C-major";
    return 0;
}