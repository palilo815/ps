#include <iostream>
using namespace std;

int main()
{
    int n[2] = { 0,1 }, N;
    cin >> N;
    for (int i = 2;i <= N;++i) {
        if (i % 2 == 0) n[0] += n[1];
        else n[1] += n[0];
    }
    cout << n[N % 2];
    return 0;
}