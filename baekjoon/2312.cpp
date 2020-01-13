#include<iostream>
#include<algorithm>
using namespace std;
struct node {
    int div;
    int count;
    node* next;
};

class linked_list
{
private:
    node* head, * tail;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }
    void add_node(int n)
    {
        if (tail != NULL && tail->div == n) {
            tail->count++;
        }
        else {
            node* tmp = new node;
            tmp->div = n;
            tmp->count = 1;
            tmp->next = NULL;
            if (head == NULL) {
                head = tmp;
                tail = tmp;
            }
            else {
                tail->next = tmp;
                tail = tail->next;
            }
        }
    }
    void Print()
    {
        node* curr = head;
        while (curr != NULL) {
            cout << curr->div << ' ' << curr->count << '\n';
            curr = curr->next;
        }
    }
};

int main()
{
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int t, n;
    cin >> t;
    while (t-- > 0) {
        cin >> n;
        linked_list ls;
        int D = 2;
        while (n != 1) {
            if (n % D == 0) {
                n /= D;
                ls.add_node(D);
            }
            else D++;
        }
        ls.Print();
    }
    return 0;
}