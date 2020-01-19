#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[5][5];
bool magic(int sum, int n)
{
    int tmp = 0;
    loop(i, n) tmp += arr[i][n - 1 - i];
    if (tmp != sum) return false;
    loop(r, n) {
        tmp = 0;
        loop(c, n) tmp += arr[r][c];
        if (tmp != sum) return false;
    }
    loop(c, n) {
        tmp = 0;
        loop(r, n) tmp += arr[r][c];
        if (tmp != sum) return false;
    }
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        loop(i, n) loop(j, n) cin >> arr[i][j];
        int sum = 0;
        loop(i, n) sum += arr[i][i];
        if (magic(sum, n)) cout << "Magic square of size " << n << '\n';
        else cout << "Not a magic square\n";
    }
    return 0;
}