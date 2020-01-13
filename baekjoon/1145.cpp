#include<iostream>
using namespace std;

int main()
{
    int num[5], count = 0, i;
    for (int i = 0; i < 5; i++)
        cin >> num[i];
    for (i = 1; count < 3;i++) {
        count = 0;
        for (int j = 0;j < 5;j++)
            if (i % num[j] == 0)
                count++;
    }
    cout << i - 1;
    return 0;
}