#include <iostream>
using namespace std;

int main()
{
    int t, leg, chi;
    cin >> t;
    while (t--) {
        cin >> leg >> chi;
        int u = chi * 2 - leg;
        cout << u << ' ' << chi - u << '\n';
    }
    return 0;
}