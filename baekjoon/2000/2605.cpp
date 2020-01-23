#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) arr[i] = i + 1;
    loop(i, n) {
        int num; cin >> num;
        loop(j, num)
            swap(arr[i - j], arr[i - j - 1]);
    }
    loop(i, n)
        cout << arr[i] << ' ';
    return 0;
}