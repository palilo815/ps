#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

int input[max_N];
int ans[max_N];
int segT[131072 * 2 - 1];

// k번째 빈 공간을 찾는다.
void find_kth(int k, int l, int r, int idx, int num)
{
    if (l == r) {
        ans[l] = num;
        ++segT[idx];
        return;
    }
    // 오른쪽 전체 공간 개수 : r - mid개
    // 이미 누가 들어간 공간 개수 : segT[2 * idx + 2]
    // 따라서 space : 오른쪽의 빈 공간 개수
    // 만약 space >= k면 오른쪽에 들어간다. 아니면 왼쪽
    int mid = l + (r - l) / 2;
    int space = r - mid - segT[2 * idx + 2];
    if (space >= k) find_kth(k, mid + 1, r, 2 * idx + 2, num);
    else find_kth(k - space, l, mid, 2 * idx + 1, num);
    ++segT[idx];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> input[i];
    for (int i = N - 1; i >= 0; --i)
        find_kth(input[i] + 1, 0, N - 1, 0, i + 1);
    for (int i = 0; i < N; ++i)
        cout << ans[i] << ' ';
    return 0;
}