#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int n; cin >> n;
    loop(i, n) {
        loop(j, n) {
            if (i % 2) cout << " *";
            else cout << "* ";
        }
        cout << '\n';
    }
    return 0;
}