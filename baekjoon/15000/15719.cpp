#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ll N; cin >> N;
    ll ans = N * (N - 1) / 2, psum = 0;
    while (N--) {
        int x; cin >> x;
        psum += x;
    }

    // ans : sum([1, n-1])
    // psum : sum([1, n-1]) + 어떤 숫자
    cout << psum - ans;
    return 0;
}