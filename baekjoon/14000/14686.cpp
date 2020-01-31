#include <iostream>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;
const int max_N = 100000;

int a[max_N + 1], b[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    int x;
    LOOP(i, n) {
        cin >> x;
        a[i] = a[i - 1] + x;
    }
    LOOP(i, n) {
        cin >> x;
        b[i] = b[i - 1] + x;
    }
    for (int i = n; i >= 0; --i)
        if (a[i] == b[i]) {
            cout << i;
            break;
        }
    return 0;
}