#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[3000];
bool Check[3000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        loop(i, n) cin >> arr[i];
        memset(Check, 0, n);
        bool J = true;
        loop(i, n - 1) {
            int gap = abs(arr[i] - arr[i + 1]);
            if (gap >= n || gap == 0) { J = false; break; }
            if (Check[gap]) { J = false; break; }
            Check[gap] = true;
        }
        if (J) cout << "Jolly\n";
        else cout << "Not jolly\n";
    }
    return 0;
}