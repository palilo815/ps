#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    string car;
    while (n--) {
        cin >> car;
        bool f = true;
        if (car[0] != car[1]) f = false;
        loop(i, 8) {
            if (i == 4) {
                if (car[i] < 'A' || car[i]>'Z') f = false;
            }
            else {
                if (car[i] > '9' || car[i] < '1') f = false;
            }
        }
        if (f) cout << car << '\n';
    }
    return 0;
}