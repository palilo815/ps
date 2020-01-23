#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T = 0, n;
    while (cin >> n) {
        if (n == 0) break;
        int Best_D = 1, Best_P = 101, d, p;
        while (n--) {
            cin >> d >> p;
            if (Best_P * d * d > p* Best_D* Best_D)
                Best_D = d, Best_P = p;
        }
        printf("Menu %d: %d\n", ++T, Best_D);
    }
    return 0;
}