#include <iostream>
using namespace std;

int main()
{
    int T, N, C;
    double G;
    cin >> T;
    while (T--) {
        cin >> N;
        int sum_C = 0;
        double sum_G = 0;
        while (N--) {
            cin >> C >> G;
            sum_C += C;
            sum_G += C * G;
        }
        cout << sum_C << ' ' << sum_G / sum_C << '\n';
    }
    return 0;
}