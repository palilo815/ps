#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100000;
int arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N_dot, N_line;
    cin >> N_dot >> N_line;
    loop(i, N_dot) cin >> arr[i];
    sort(arr, arr + N_dot);

    int l, r;
    while (N_line--) {
        cin >> l >> r;
        cout << upper_bound(arr, arr + N_dot, r) - lower_bound(arr, arr + N_dot, l) << '\n';
    }
    return 0;
}