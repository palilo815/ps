#include<iostream>
#include<string>
using namespace std;
int main()
{
    string A, B;
    cin >> A >> B;
    int gap = B.length() - A.length() + 1;
    int min = A.length();
    for (int i = 0; i < gap; i++) {
        int count = 0;
        for (int j = 0; j < A.length(); j++) {
            if (A[j] != B[i + j])
                count++;
        }
        if (count < min)
            min = count;
    }
    cout << min;
    return 0;
}