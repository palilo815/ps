#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> p;

const int max_N = 100000;

p arr[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> arr[i].second;
    loop(i, N) cin >> arr[i].first;
    sort(arr, arr + N);
    
    ll ans = 0;
    loop(i, N) {
        auto [d, h] = arr[i];
        ans += (ll)i * d + h;
    }
    cout << ans;
    return 0;
}