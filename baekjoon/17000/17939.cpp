#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;

int price[max_N];
int p_max[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> price[i];
    
    for (int i = N - 2; i >= 0; --i)
        p_max[i] = max(price[i + 1], p_max[i + 1]);

    int money = 0, coin = 0;
    loop(i, N) {
        if (price[i] < p_max[i]) money -= price[i], ++coin;
        else money += coin * price[i], coin = 0;
    }
    cout << money;
    return 0;
}