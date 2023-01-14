//
// Created by JODE on 2023-01-14.
//
#include <iostream>
using namespace std;

bool isSameTree(TreeNode* p, TreeNode* q) {
    if ((p == NULL && q == NULL) || (p->val && q->val))
        return true;
    else
        return false;
    bool ans = (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
    return ans;
}