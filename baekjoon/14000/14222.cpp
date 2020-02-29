#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 50;

int arr[max_N];
bool check[max_N + 1];

int main() {
    int N, K; cin >> N >> K;
    loop(i, N) cin >> arr[i];
    sort(arr, arr + N);
    loop(i, N) {
        int num = arr[i];
        while (num <= N && check[num]) num += K;
        if (num > N) { cout << 0; return 0; }
        check[num] = true;
    }
    cout << 1;
    return 0;
}