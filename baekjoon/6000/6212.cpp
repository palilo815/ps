#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int arr[10];
void counting(int n)
{
    while (n) {
        ++arr[n % 10];
        n /= 10;
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int a, b; cin >> a >> b;
    for (int i = a; i <= b; ++i)
        counting(i);
    loop(i, 10) cout << arr[i] << ' ';
    return 0;
}