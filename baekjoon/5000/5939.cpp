#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[5000];
int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, h, m, s;
    cin >> n;
    loop(i, n) {
        cin >> h >> m >> s;
        arr[i] = h * 10000 + m * 100 + s;
    }
    sort(arr, arr + n);
    loop(i, n) {
        int h = arr[i];
        s = h % 100; h /= 100;
        m = h % 100; h /= 100;
        cout << h << ' ' << m << ' ' << s << '\n';
    }
    return 0;
}