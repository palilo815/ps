#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[29][3];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) loop(j, 3) cin >> arr[i][j];
    cout << "Gnomes:\n";
    loop(i, n)
        if ((arr[i][0] <= arr[i][1] && arr[i][1] <= arr[i][2]) || (arr[i][0] >= arr[i][1] && arr[i][1] >= arr[i][2])) cout << "Ordered\n";
        else cout << "Unordered\n";
    return 0;
}