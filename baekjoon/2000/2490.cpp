#include<iostream>
using namespace std;

int main()
{
    int a[12], i;
    for (i = 0; i < 12; i++)
        cin >> a[i];
    for (i = 0; i < 12; i += 4) {
        char c = 'D' - a[i] - a[i + 1] - a[i + 2] - a[i + 3];
        if (c == '@') cout << "E";
        else cout << c;
        cout << endl;
    }
    return 0;
}