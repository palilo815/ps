#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int word[50];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    int ans = 0;

    // bitmask로 풀어보자
    // 근데 풀고보니 백트레킹이 더 나은듯
    loop(i, N) {
        string s; cin >> s;
        int tmp = 0, len = s.size();
        loop(j, len)
            tmp |= 1 << (s[j] - 'a');
        word[i] = tmp;
    }
    // word[i]엔, 해당 글자에 들어가는 알파벳 정보가 들어간다.

    loop(i, 1 << 26)
        if (__builtin_popcount(i) == K) {
            int cnt = 0;
            loop(j, N)
                if ((word[j] & i) == word[j]) ++cnt;
            ans = max(ans, cnt);
        }
    cout << ans;
    return 0;
}