#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int In[100000], Post[100000];
void PreOrder(int s_in, int e_in, int s_post, int e_post)
{
    if (s_in > e_in) return;
    int m = Post[e_post];
    cout << m << ' ';
    if (s_in == e_in) return;

    int line_in = e_in, line_post = e_post;
    while (In[line_in] != m)
        --line_in, --line_post;
    PreOrder(s_in, line_in - 1, s_post, line_post - 1);
    PreOrder(line_in + 1, e_in, line_post, e_post - 1);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n; cin >> n;
    loop(i, n) cin >> In[i];
    loop(i, n) cin >> Post[i];
    PreOrder(0, n - 1, 0, n - 1);
    return 0;
}