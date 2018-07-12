
#include <iostream>
#include <string>
#include "decoder.h"
using namespace std;

Node* Decode::getRoot()
{
    return root;
}

void Decode::addleaf_at(int val, string strng_bin) {
    Node *curr;
    curr = root;
    for (int i = 0; i < strng_bin.length(); i++) {
        if (strng_bin.at(i) == '0') {
            if (curr->left == NULL) {
                Node* newNode = new (struct Node);
                curr->left = newNode;
            }
            curr = curr->left;
        }
        else if (strng_bin.at(i) == '1') {
            if (curr->right == NULL) {
                Node* newNode = new (struct Node);
                curr->right = newNode;
            }
            curr = curr->right;
        }
    }
    curr->value = val;
    curr->isLeaf = true;
}

int Decode::extract(string bin_strng) {
    Node *curr;
    curr = root;

    for (int i = 0; i < bin_strng.length(); i++) {
        if (curr == NULL) {
            return -1;
        }
        else if (bin_strng.at(i) == '0') {
            curr = curr->left;
        }
        else if (bin_strng.at(i) == '1') {
            curr = curr->right;
        }
    }
    if (curr->isLeaf == true) {
        return curr->value;
    }
    else {
        return -1;
    }
}



