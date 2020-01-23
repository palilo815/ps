#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int work[50];
int main()
{
    int n, T, ans = 0, sum = 0;
    cin >> n >> T;
    loop(i, n) cin >> work[i];
    loop(i, n) {
        if (sum + work[i] <= T) {
            sum += work[i];
            ++ans;
        }
        else break;
    }
    cout << ans;
    return 0;
}