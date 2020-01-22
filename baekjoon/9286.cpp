#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[500];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n; cin >> n;
        loop(j, n) cin >> arr[j];
        cout << "Case " << i << ":\n";
        loop(j, n) {
            if (arr[j] == 6) continue;
            cout << arr[j] + 1 << '\n';
        }
    }
    return 0;
}