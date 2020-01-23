#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    int price, n, won = 1;
    cin >> price >> n;
    while (n--) won *= 10;

    int trash = price % won;
    if (trash >= won - trash)
        price = price - trash + won;
    else
        price -= trash;
    cout << price;
    return 0;
}