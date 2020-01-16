#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[20001];
int Count(int N, int div)
{
    int ret = 0;
    while (N) {
        ret += N / div;
        N /= div;
    }
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int two = Count(N, 2);
    int five = Count(N, 5);
    if (two < five) five = two;
    else two = five;

    // arr[i]에 i를 집어넣되,
    // 2와 5로 나눈다음에 집어넣는다.
    for (int i = 1; i <= N; ++i) {
        arr[i] = i;
        while (two && (arr[i] % 2 == 0)) {
            arr[i] /= 2;
            --two;
        }
        while (five && (arr[i] % 5 == 0)) {
            arr[i] /= 5;
            --five;
        }
    }

    // 이제 arr를 다시 다 곱한 뒤, 10으로 나누면 정답이다.
    int ans = 1;
    for (int i = 1; i <= N; ++i) {
        ans *= arr[i];
        ans %= 10;
    }
    cout << ans;
    return 0;
}