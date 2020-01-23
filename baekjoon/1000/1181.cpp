#include<iostream>
#include<algorithm>
using namespace std;

bool MySort(string s1, string s2)
{
    if (s1.length() == s2.length())
        return s1 < s2;
    else
        return (s1.length() < s2.length()) ? true : false;
}
int main()
{
    int n;
    cin >> n;
    string* arr = new string[n];
    string s;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n, MySort);
    cout << arr[0] << endl;
    for (int i = 1; i < n; i++)
        if (arr[i] != arr[i - 1])
            cout << arr[i] << endl;
    return 0;
}