#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define ll long long

// val[i] : i번 알파벳의 가치
ll val[10];
// 앞자리에 쓰였는지 여부
// 만약 F_digit[i] == true면 i번 알파벳은 0이 되면 안된다.
bool F_digit[10];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        F_digit[s[0] - 'A'] = true;
        reverse(s.begin(), s.end());
        loop(i, s.length())
            val[s[i] - 'A'] += pow(10, i);
    }
    // 앞자리에 안 쓰인 알파벳 중
    // 가장 값이 떨어지는 애를 찾는다.
    ll tmp = INT64_MAX;
    int ind;
    loop(i, 10) {
        if (val[i] < tmp && !F_digit[i]) {
            tmp = val[i];
            ind = i;
        }
    }
    val[ind] = INT64_MAX;
    sort(val, val + 10);

    ll ans = 0;
    // 앞의 9개만 고려한다.
    // 순서대로 1, 2, ..., 9를 부여해주면 된다.
    loop(i, 9)
        ans += (ll)val[i] * (i + 1);
    cout << ans;
    return 0;
}