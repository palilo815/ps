#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int val[26];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string s;
    int N; cin >> N;

    // val[i]에 i번 알파벳의 가치를 저장한다.
    // ex) ABCD에서 A의 가치는 1000, B는 100, C는 10, D는 1
    while (N--) {
        cin >> s;
        int len = s.size();
        loop(i, len)
            val[s[i] - 'A'] += pow(10, len - i - 1);
    }
    sort(val, val + 26, greater<int>());
    int ans = 0;

    // 가치가 높은 알파벳에게 9부터 순서대로 부여함
    loop(i, 10)
        ans += (9 - i) * val[i];
    cout << ans;
    return 0;
}