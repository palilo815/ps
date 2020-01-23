#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int a, b, n = 1, sum = 0;
    cin >> a >> b;
    vector<int> v;
    // 직접 b개 다 넣은 뒤
    while (v.size() < b) {
        for (int i = 0; i < n; ++i)
            v.push_back(n);
        n++;
    }
    // 원하는 구간만 합함
    for (int i = a - 1; i < b; ++i)
        sum += v[i];
    cout << sum;
    return 0;
}