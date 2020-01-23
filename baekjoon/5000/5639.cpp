#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

vector<int> v;
int l = 0;
void s(int r)
{
    if (l == v.size() || v[l] > r) return;
    int R = v[l++];
    s(R);
    s(r);
    cout << R << '\n';
}
int main()
{
    int n;
    while (cin >> n)
        v.push_back(n);
    int r = v[l++];
    s(r);
    s(INT_MAX);
    cout << r << '\n';
    return 0;
}