#include <bits/stdc++.h> 
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[5000000];

int pivot(int l, int r)
{
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}
int kth(int l, int r, int k)
{
    if (k > 0 && k <= r - l + 1) {
        int idx = pivot(l, r);
        if (idx - l == k - 1) return arr[idx];
        if (idx - l > k - 1) return kth(l, idx - 1, k);
        return kth(idx + 1, r, k - idx + l - 1);
    }
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    loop(i, N) cin >> arr[i];
    cout << kth(0, N - 1, K);
    return 0;
}