#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int song, ave, ans = 1;
    cin >> song >> ave;
    while (ceil(double(ans) / double(song)) != ave)
        ans++;
    cout << ans;
    return 0;
}