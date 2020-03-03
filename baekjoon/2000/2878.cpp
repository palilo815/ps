#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef unsigned long long ull;

const int max_N = 100000;

int need[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    ull candy; int N;
    cin >> candy >> N;
    ull lack = 0;
    loop(i, N) {
        cin >> need[i];
        lack += need[i];
    }

    lack -= candy;
    sort(need, need + N);
    
    ull ans = 0;
    loop(i, N) {
        ull anger = min((ull)need[i], lack / (N - i));
        lack -= anger;
        ans += anger * anger;
    }
    cout << ans;
    return 0;
}