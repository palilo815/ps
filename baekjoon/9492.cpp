#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

string card[1000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        if (n == 0) break;
        loop(i, n) cin >> card[i];
        int half = n / 2;
        if (n % 2) {
            loop(i, half)
                cout << card[i] << '\n' << card[i + half + 1] << '\n';
            cout << card[half] << '\n';
        }
        else
            loop(i, half)
            cout << card[i] << '\n' << card[i + half] << '\n';
    }
    return 0;
}