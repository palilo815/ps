#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int arr[5];
    loop(i, 5) cin >> arr[i];
    bool update = true;
    while (update) {
        update = false;
        loop(i, 4)
            if (arr[i] > arr[i + 1]) {
                update = true;
                swap(arr[i], arr[i + 1]);
                loop(j, 5) cout << arr[j] << ' ';
                cout << '\n';
            }
    }
    return 0;
}