//
//  main.cpp
//  leetcodeTest
//
//  Created by Shawn An on 2018-11-07.
//  Copyright © 2018 Shawn An. All rights reserved.
//

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
    Node* prev;
    Node* next;
    Node(int x) {
        val = x;
        prev = NULL;
        next = NULL;
    }
    ~Node() {
        prev = NULL;
        next = NULL;
    }
};

class DLL {
public:
    Node* head = new Node(0);
    DLL(vector<int>& x) {
        if (x.size() == 0) return;
        sort(x.begin(),x.end());
        Node* tempFast;
        Node* tempSlow = head;
        for (int i = 0; i < x.size(); i ++) {
            tempFast = new Node(x[i]);
            tempFast -> prev = tempSlow;
            tempSlow -> next = tempFast;
            tempSlow = tempFast;
        }
        head = head->next;
        head-> prev = NULL;
    }
    void print() {
        Node* temp = head;
        Node* slow;
        cout << "ASC Nodes: ";
        while (temp) {
            cout << temp->val << " -> ";
            slow = temp;
            temp= temp->next;
        }
        cout <<"nullptr\n";
        cout << "DSC Nodes: ";
        while (slow) {
            cout << slow->val << " -> ";
            slow = slow->prev;
        }
        cout <<"nullptr\n--------------------\n";
    }
    
    void modify(int val, int subtrahend) {
        if (subtrahend == 0) return;
        cout << "Node to find is: " << val << " ,subtrachend is: " << subtrahend << "\n\n";
        Node* oP = NULL;
        Node* oN = NULL;
        Node* temp = head;
        bool foundOldPos = false;
        bool foundNewPos = false;
        // delete
        while (temp&& !foundOldPos) {
            if (temp -> val == val) {
                oP = temp->prev;
                oN = temp->next;
                foundOldPos = true;
            }
            temp = temp->next;
        }
        if (!foundOldPos) return;
        if (oP) oP->next = oN;
        else head = oN;
        if (oN) oN->prev = oP;
        
        // insert
        Node* nP = NULL;
        Node* nN = head;
        temp = head;
        Node* addedNode = new Node(val-subtrahend);
        while (temp && !foundNewPos) {
            if (temp->val <= val-subtrahend) {
                nP = temp;
                nN = temp->next;
            }else {
                foundNewPos = true;
            }
            temp = temp->next;
        }
        if (nP) {
            nP->next = addedNode;
            addedNode->prev = nP;
        } else {
            head = addedNode;
        }
        
        if (nN) {
            addedNode->next = nN;
            nN->prev = addedNode;
        }
    }
};



int main() {
    vector<int> list = {1,2,4,6};
    DLL* dll = new DLL(list);
    dll->print();
    dll->modify(-1,3);
    dll->print();
    return 0;
}



