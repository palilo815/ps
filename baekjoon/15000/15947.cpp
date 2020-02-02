#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int n, s, w;
    cin >> n;
    s = n / 14, w = n % 14;
    if (w == 0 || w == 2) cout << "sukhwan";
    else if (w == 1 || w == 13) cout << "baby";
    else if (w == 5) cout << "very";
    else if (w == 6) cout << "cute";
    else if (w == 9) cout << "in";
    else if (w == 10) cout << "bed";
    else {
        int ru = 1 + (w % 2);
        ru += s;
        if (ru < 5) {
            cout << "tu";
            loop(i, ru) cout << "ru";
        }
        else
            cout << "tu+ru*" << ru;
    }
    return 0;
}