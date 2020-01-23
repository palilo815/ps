#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) {
        loop(j, n) {
            if (j % 2) cout << ' ';
            else cout << '*';
        }
        cout << '\n';
        loop(j, n) {
            if (j % 2) cout << '*';
            else cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}