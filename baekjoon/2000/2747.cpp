#include<iostream>
using namespace std;
int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n[2] = { 0,1 }, N, i;
    cin >> N;
    for (i = 2; i <= N;i++) {
        if (i % 2 == 0) n[0] += n[1];
        else n[1] += n[0];
    }
    cout << n[N % 2];
    return 0;
}