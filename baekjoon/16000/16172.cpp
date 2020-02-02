#include <bits/stdc++.h>
using namespace std;

vector<int> get_partial_match(string& needle)
{
    int M = needle.size();
    vector<int> pi(M);
    int begin = 1, matched = 0;
    while (begin + matched < M) {
        if (needle[begin + matched] == needle[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else {
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}
bool kmp_search(string& haystack, string& needle)
{
    int N = haystack.size(), M = needle.size();
    vector<int> pi = get_partial_match(needle);
    int begin = 0, matched = 0;
    while (begin <= N - M) {
        if (matched < M && haystack[begin + matched] == needle[matched]) {
            ++matched;
            if (matched == M) return true;
        }
        else {
            if (matched == 0) ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    string hay = "", needle;
    char x;
    while (cin.peek() != '\n') {
        cin >> x;
        if (x < '0' || x > '9') hay += x;
    }
    cin.ignore();
    cin >> needle;
    cout << kmp_search(hay, needle);
    return 0;
}