#include<iostream>
#include<string>
#include<algorithm>
#include<map>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    map<string, int> ToOct
    {
        {"000", 0},
        {"001", 1},
        {"010", 2},
        {"011", 3},
        {"100", 4},
        {"101", 5},
        {"110", 6},
        {"111", 7},
    };
    string num;
    cin >> num;
    if (num.length() % 3 != 0) {
        int add = num.length() % 3;
        num.insert(0, 3 - add, '0');
    }

    for (int i = 0; i < num.length(); i += 3)
        cout << ToOct.find(num.substr(i, 3))->second;
    return 0;
}