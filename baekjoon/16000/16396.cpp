#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool line[10001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, a, b;
    cin >> n;
    while (n--) {
        cin >> a >> b;
        for (int i = a; i < b; ++i)
            line[i] = true;
    }

    int ans = 0;
    loop(i, 10001)
        if (line[i]) ++ans;
    cout << ans;
    return 0;
}