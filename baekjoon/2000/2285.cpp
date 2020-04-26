#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> p;

const int max_N = 100000;

p city[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    ll total = 0;
    loop(i, N) {
        cin >> city[i].first >> city[i].second;
        total += city[i].second;
    }
    sort(city, city + N);

    total /= 2;
    ll sum = 0;
    loop(i, N) {
        sum += city[i].second;
        if (sum >= total) {
            cout << city[i].first;
            break;
        }
    }
    return 0;
}