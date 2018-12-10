
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <unordered_map>
#include <queue>
#include <map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node(int x) {
        val = x;
        next = NULL;
    }
};
class LinkedList {
public:
    Node* head;
    LinkedList(vector<int> v) {
        Node* t;
        for(int i = 0; i < v.size(); i++) {
            Node* temp = new Node(v[i]);
            if (i == 0) {
                head = temp;
                t = head;
            }
            else {
                assert(t!=NULL);
                t->next = temp;
                t = t->next;
            }
        }
    }
    void print() {
        cout <<"Node sequences are: ";
        Node* temp = head;
        while (temp) {
            cout << temp->val << "->";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
    void reverse() {
        cout <<"Reverse!\n";
        Node* prev = NULL;
        Node* next = NULL;
        Node* curr = head;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
    void recRevHelper(Node*x, Node*y) {
        
        Node* t;
        if(y) {
            t = y->next;
            y->next= x;
            recRevHelper(y,t);
        } else {
            head = x;
        }
    }
    void recRev() {
        cout << "Recursive Reverse!\n";
        recRevHelper(NULL,head);
    }
};


int main() {
    vector <int> k = {1,2,3,4,5};

    LinkedList ll(k);
    ll.print();
    ll.reverse();
    ll.print();
    ll.recRev();
    ll.print();

    return 0;
}
