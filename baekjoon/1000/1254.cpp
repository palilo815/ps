#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s; cin >> s;
    int ans = -1; // 덧붙이는 개수
    bool palin = false;
    while (!palin) {
        ++ans;
        int l = ans, r = s.size() - 1;
        if (l == r) break;

        // 앞에서 ans개의 문자와 똑같은 문자를 뒤에 붙이면 되므로
        // 앞에서 ans개 만큼은 제외하고 나머지가 palindrome인지 비교
        palin = true;
        while (l < r)
            if (s[l++] != s[r--]) {
                palin = false;
                break;
            }
    }
    cout << s.size() + ans;
    return 0;
}