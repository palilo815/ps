#include<iostream>
using namespace std;

int main()
{
    int N, T, a, count = 0;
    cin >> N >> T;
    int* arr = new int[T + 1];
    for (int i = 0; i < T + 1; i++)
        arr[i] = 0;
    while (N-- > 0) {
        cin >> a;
        for (int i = 1; i <= T; i++) {
            if (i % a == 0) {
                if (arr[i] == 0) {
                    count++;
                    arr[i] = 1;
                }
            }
        }
    }
    cout << count;
    return 0;
}