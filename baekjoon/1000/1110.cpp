#include<iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int tmp = N, count = 0;
    do {
        int right = (tmp / 10 + tmp % 10) % 10;
        tmp = (tmp % 10) * 10 + right;
        count++;
    } while (tmp != N);
    cout << count;
    return 0;
}