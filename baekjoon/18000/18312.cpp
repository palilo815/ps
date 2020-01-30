#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool has_K(int n, int K)
{
    if (n % 10 == K || n / 10 == K) return true;
    return false;
}
int main()
{
    int N, K; cin >> N >> K;
    int ans = 0;
    loop(h, N + 1) {
        if (has_K(h, K)) ans += 3600;
        else {
            loop(m, 60) {
                if (has_K(m, K)) ans += 60;
                else loop(s, 60) ans += has_K(s, K);
            }
        }
    }
    cout << ans;
    return 0;
}