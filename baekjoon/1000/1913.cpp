#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[1000][1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, key, x = 1, len;
    cin >> n >> key;
    int r = n / 2, c = r;
    arr[r][c] = x++;
    loop(i, n / 2) {
        len = 2 * i + 1;
        loop(a, len) arr[--r][c] = x++;
        loop(a, len) arr[r][++c] = x++;
        ++len;
        loop(a, len) arr[++r][c] = x++;
        loop(a, len) arr[r][--c] = x++;
    }
    loop(a, len)
        arr[--r][c] = x++;
    loop(i, n) {
        loop(j, n) {
            cout << arr[i][j] << ' ';
            if (arr[i][j] == key) r = i + 1, c = j + 1;
        }
        cout << '\n';
    }
    cout << r << ' ' << c;
    return 0;
}