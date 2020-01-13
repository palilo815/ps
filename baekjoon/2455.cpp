#include<iostream>
using namespace std;

int main()
{
    int T = 4, in, out, sum = 0, max = 0;
    while (T-- > 0) {
        cin >> out >> in;
        sum += (in - out);
        if (sum > max)
            max = sum;
    }
    cout << max;
    return 0;
}