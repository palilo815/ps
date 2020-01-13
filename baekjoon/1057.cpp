#include<iostream>
using namespace std;

int main()
{
    int N, A, B;
    cin >> N >> A >> B;
    int round = 0;
    while (A != B) {
        A = (A + 1) / 2;
        B = (B + 1) / 2;
        round++;
    }
    cout << round;
    return 0;
}