#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T, arr[3];
    string s[2] = { "NO","YES" };
    cin >> T;
    loop(t, T) {
        loop(i, 3) cin >> arr[i];
        sort(arr, arr + 3);
        int X = pow(arr[0], 2) + pow(arr[1], 2), Y = pow(arr[2], 2);
        cout << "Case #" << t + 1 << ": " << s[X == Y] << '\n';
    }
    return 0;
}