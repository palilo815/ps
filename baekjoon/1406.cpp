#include<iostream>
#include<list>
#include<iterator>
using namespace std;

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    char c;
    list<char> word;

    while (cin.peek() != '\n') {
        cin >> c;
        word.push_back(c);
    }
    cin >> n;
    list<char>::iterator cursor = word.end();

    while (n-- > 0) {
        cin >> c;
        switch (c) {
        case 'L':
            if (cursor != word.begin())
                cursor--;
            break;
        case 'D':
            if (cursor != word.end())
                cursor++;
            break;
        case 'B':
            if (cursor != word.begin())
                cursor = word.erase(--cursor);
            break;
        case 'P':
            cin >> c;
            word.insert(cursor, c);
            break;
        }
    }
    for (list<char>::iterator it = word.begin(); it != word.end();it++)
        cout << *it;
    return 0;
}