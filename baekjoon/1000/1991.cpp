#include<iostream>
using namespace std;

typedef struct node {
    char name;
    struct node* left;
    struct node* right;
} Node;

char arr[78];

void MakeTree(Node* root);
int FindIndex(char name);
Node* NewNode(char name);
void PreOrder(Node* root);
void InOrder(Node* root);
void PostOrder(Node* root);

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 0; i < 3 * n; i++)
        cin >> arr[i];
    Node root;
    root.name = 'A';
    MakeTree(&root);

    PreOrder(&root);
    cout << '\n';
    InOrder(&root);
    cout << '\n';
    PostOrder(&root);
    return 0;
}
void MakeTree(Node* root)
{
    if (root == NULL) return;
    else {
        int index = FindIndex(root->name);
        root->left = NewNode(arr[index + 1]);
        root->right = NewNode(arr[index + 2]);
        MakeTree(root->left);
        MakeTree(root->right);
    }
}
int FindIndex(char name)
{
    for (int i = 0; i < 78; i += 3)
        if (arr[i] == name)
            return i;
    return -1;
}
Node* NewNode(char name)
{
    if (name == '.') return NULL;
    else {
        Node* tmp = new Node;
        tmp->name = name;
        return tmp;
    }
}
void PreOrder(Node* root)
{
    if (root == NULL) return;
    cout << root->name;
    PreOrder(root->left);
    PreOrder(root->right);
}
void InOrder(Node* root)
{
    if (root == NULL) return;
    InOrder(root->left);
    cout << root->name;
    InOrder(root->right);
}
void PostOrder(Node* root)
{
    if (root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->name;
}