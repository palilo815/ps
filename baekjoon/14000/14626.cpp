#include <iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    string s; cin >> s;
    int sum = 0, miss;

    loop(i, 13) {
        if (s[i] == '*') {
            miss = i;
            continue;
        }
        int x = s[i] - '0';
        if (i % 2) x *= 3;
        sum += x;
    }
    sum %= 10;

    if (miss % 2) {
        loop(i, 10)
            if ((sum + 3 * i) % 10 == 0) {
                cout << i;
                break;
            }
    }
    else {
        loop(i, 10)
            if ((sum + i) % 10 == 0) {
                cout << i;
                break;
            }
    }
    return 0;
}