#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define CNT(x) (upper_bound(psum.begin(),psum.end(),x)-lower_bound(psum.begin(),psum.end(),x))
using namespace std;

const int M = 1000;

int a[M], b[M];
vector<int> psum;

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, A, B; cin >> N >> A >> B;
    loop(i, A) cin >> a[i];
    loop(i, B) cin >> b[i];

    int ans = 0, total;
    loop(i, B) {
        int s = 0;
        loop(j, B - 1) {
            int k = (i + j) % B;
            s += b[k];
            if (s < N) psum.emplace_back(s);
            else {
                ans += s == N;
                break;
            }
        }
    }
    sort(psum.begin(), psum.end());

    total = accumulate(b, b + B, 0);
    if (total >= N) ans += total == N;
    else psum.emplace_back(total);

    loop(i, A) {
        int s = 0;
        loop(j, A - 1) {
            int k = (i + j) % A;
            s += a[k];
            if (s < N) ans += CNT(N - s);
            else {
                ans += s == N;
                break;
            }
        }
    }

    total = accumulate(a, a + A, 0);
    if (total >= N) ans += total == N;
    else ans += CNT(N - total);
    cout << ans;
    return 0;
}