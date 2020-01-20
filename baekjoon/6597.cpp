#include<iostream>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

string Pre, In;
void Post(int s_pre, int e_pre, int s_in, int e_in)
{
    if (s_pre > e_pre) return;
    char m = Pre[s_pre];
    if (s_pre != e_pre) {
        int line_pre = s_pre, line_in = s_in;
        while (In[line_in] != m) ++line_pre, ++line_in;
        Post(s_pre + 1, line_pre, s_in, line_in - 1);
        Post(line_pre + 1, e_pre, line_in + 1, e_in);
    }
    cout << m;
}
int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    while (cin >> Pre >> In) {
        Post(0, Pre.size() - 1, 0, Pre.size() - 1);
        cout << '\n';
    }
    return 0;
}