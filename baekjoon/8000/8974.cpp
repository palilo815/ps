#include <iostream>
#include <vector>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

int main()
{
    int a, b, i = 1;
    cin >> a >> b;
    vector<int> vt;
    vt.reserve(b);
    while (1) {
        loop(j, i) {
            vt.push_back(i);
            if (vt.size() == b) goto OUT;
        }
        ++i;
    }
OUT:;
    int sum = 0;
    for (int k = a - 1; k < b;++k)
        sum += vt[k];
    cout << sum;
    return 0;
}