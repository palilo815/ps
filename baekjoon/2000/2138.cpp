#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int max_N = 100000;

bool goal[max_N + 2];
bool arr1[max_N + 2], arr2[max_N + 2];
int find_ans(bool arr[], int N)
{
    int ret = 0;
    LOOP(i, N - 1)
        // i, i+1, i+2를 바꾼다.
        // 어차피 i는 나중에 고려 안하므로, 실제로 바꾸는건 i+1,i+2만 해주면 된다.
        if (arr[i] != goal[i]) {
            ++ret;
            arr[i + 1] = !arr[i + 1];
            arr[i + 2] = !arr[i + 2];
        }

    // arr2는 함수 호출 후 +1을 해주므로 overflow 방지를 위한 -1
    if (arr[N] != goal[N]) ret = INT_MAX - 1;
    return ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    char x;
    LOOP(i, N) {
        cin >> x;
        if (x == '1') arr1[i] = true;
    }
    LOOP(i, N) {
        cin >> x;
        if (x == '1') goal[i] = true;
    }
    // arr1 : input 그대로
    // arr2 : input에서 1번 스위치를 누른 상태
    memcpy(arr2, arr1, sizeof(arr1));
    arr2[1] = !arr2[1];
    arr2[2] = !arr2[2];

    // 각 arr에서 goal모양을 만드는데 필요한 횟수를 구한뒤 최솟값을 취한다.
    // arr2는 이미 1번을 누른 상태므로 +1을 해줘야 한다.
    int ans = min(find_ans(arr1, N), find_ans(arr2, N) + 1);
    if (ans  > max_N) cout << -1;
    else cout << ans;
    return 0;
}