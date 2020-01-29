#include <iostream>
using namespace std;

int main()
{
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    if (s2[0] == 'A') {
        if (s1[0] == 't' && s3[0] == 't') cout << s1;
        else cout << "false";
    }
    else {
        if (s1[0] == 'f' && s3[0] == 'f') cout << s1;
        else cout << "true";
    }
    return 0;
}