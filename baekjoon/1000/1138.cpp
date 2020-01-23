#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, arr[10];
    cin >> n;
    loop(i, n) cin >> arr[i];
    vector<int> ans(n);

    // 작은 사람부터 차례로 놓는다.
    loop(i, n) {
        int left = arr[i], idx = 0;
        // 만약 나보다 큰 사람이 3명 왼쪽에 있었다면
        // 왼쪽에 빈 공간 3개를 만들어놔야 한다.

        // left개의 빈 공간이 나올때까지 idx를 오른쪽으로 옮김
        while (left) {
            if (!ans[idx]) --left;
            ++idx;
        }
        // idx가 빈 자리가 될 때까지 오른쪽으로 옮김
        while (ans[idx]) idx++;
        // 이 아이가 있을 자리는 idx다.
        ans[idx] = i + 1;
    }
    loop(i, n) cout << ans[i] << ' ';
    return 0;
}