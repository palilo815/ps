#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_base = 1000000;

// sieve[]  : 에라토스 체
// sqr_ss[] : 제곱ㄴㄴ
bool sieve[max_base + 1];
bool sqr_ss[max_base + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 일단 1,000,000이하의 소수를 전부 구한다.
    // 1,000,000 ^ 2 <= max_R < 1,000,001 ^ 2
    sieve[0] = sieve[1] = true;
    for (int i = 2; i * i <= max_base; ++i)
        if (!sieve[i])
            for (int j = i * i; j <= max_base; j += i)
                sieve[j] = true;

    // [L,R]구간의 수를 전부 제곱ㄴㄴ = true라고 한 뒤
    // 제곱수로 나누어 떨어질 경우 false로 바꾼다.
    ll L, R; cin >> L >> R;
    fill(sqr_ss, sqr_ss + (R - L) + 1, true);

    // 에라토스 체랑 비슷한 원리로 작동한다.
    for (int i = 2; i <= max_base; ++i) {
        if (!sieve[i]) {
            ll sqr = 1ll * i * i;
            for (ll j = ((L - 1) / sqr + 1) * sqr; j <= R; j += sqr)
                sqr_ss[j - L] = false;
        }
    }

    int ans = 0;
    for (int i = 0; i <= R - L; ++i)
        if (sqr_ss[i]) ++ans;
    cout << ans;
    return 0;
}