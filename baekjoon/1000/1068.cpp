#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> graph;
bool visited[50]{};
int count_leaf = 0;

void dfs(int here)
{
    visited[here] = true;
    bool leaf = true;
    for (int i = 0; i < graph[here].size();i++) {
        int there = graph[here][i];
        if (!visited[there]) {
            dfs(there);
            leaf = false;
        }
    }
    if (leaf) count_leaf++;
}

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n, parent, root, del;
    cin >> n;
    graph.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> parent;
        if (parent != -1)
            graph[parent].push_back(i);
        else root = i;
    }
    cin >> del;
    visited[del] = true;
    if (!visited[root])
        dfs(root);
    cout << count_leaf;
    return 0;
}