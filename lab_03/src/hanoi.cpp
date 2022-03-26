#include <iostream>
#include <string>
#include <vector>
using i64 = long long;
using namespace std;


struct Node {
    string val;
    Node* next;

    Node(string _val) : val(_val), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    bool is_empty() {
        return first == nullptr;
    }

    void push_back(string _val) {
        Node* p = new Node(_val);
        
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void print() {
        if (is_empty()) {
            cout << "Empty list"; 
            return;
        }
        Node* p = first;

        while (p) {
            cout << p->val << endl;
            p = p->next;
        }
    }

    void clear() {
        Node* p = first;

        while (p) {
            cout << p->val << " deleted" << endl;
            delete p;
            p = p->next;
        }
    }
};


template <typename T>
T hanoi_generic(i64 n, int i, int k, T res) {
    int tmp;

    if (n == 1) {
        res.push_back("Move disk 1 from pin " + to_string(i) + " to " + to_string(k));
        return res;
    }
    else {
        tmp = 6 - i - k;
        res = hanoi_generic(n - 1, i, tmp, res);
        res.push_back("Move disk " + to_string(n) + " from pin " + to_string(i) + " to " + to_string(k));
        res = hanoi_generic(n - 1, tmp, k, res);
        return res;
    }
}
 
int main(int argc, char** argv)
{
    i64 n = 3;
    vector<string> res;
    list lst;

    // res = hanoi(n, 1, 2, res);
    // lst = hanoi_list(n, 1, 2, lst);

    res = hanoi_generic(n, 1, 2, res);
    lst = hanoi_generic(n, 1, 2, lst);

    for (auto i: res) cout << i << endl;
    cout << endl;
    lst.print();
    lst.clear();

    return 0;
}

