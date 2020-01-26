#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[100000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 소수를 사용하면 오차가 나도록 만든 문제
    // 소수를 *10해서 정수의 형태로 arr에 저장
    int N, K; cin >> N >> K;
    loop(i, N) {
        double d; cin >> d;
        arr[i] = d * 10;
    }
    sort(arr, arr + N);

    // 각각의 평균을 계산해준다.
    // 계산한 후에, 100을 곱해준다. (총 1000이 곱해진 상태)
    int avg1 = 0, avg2 = 0;
    for (int i = K;i < N - K;++i)
        avg1 += arr[i], avg2 += arr[i];
    avg2 += (arr[K] + arr[N - K - 1]) * K;
    avg1 = 100 * avg1 / (N - 2 * K);
    avg2 = 100 * avg2 / N;

    // 반올림과정
    // 원래 숫자에 1000이 곱해졌으므로,
    // 0.001에 해당하는 숫자는 일의 자리에 있다.
    if (avg1 % 10 >= 5) avg1 += 10;
    if (avg2 % 10 >= 5) avg2 += 10;
    // 0.001자리 삭제
    avg1 /= 10, avg2 /= 10;

    // ex) 3.14가 314로 저장되어있다.
    cout << avg1 / 100 << '.' << (avg1 / 10) % 10 << avg1 % 10 << '\n';
    cout << avg2 / 100 << '.' << (avg2 / 10) % 10 << avg2 % 10;
    return 0;
}