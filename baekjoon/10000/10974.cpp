#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int max_N = 8;

int arr[max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) arr[i] = i + 1;
    do {
        loop(i, n) cout << arr[i] << ' ';
        cout << '\n';
    } while (next_permutation(arr, arr + n));
    return 0;
}