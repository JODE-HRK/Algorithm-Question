//
// Created by JODE on 2023-01-23.
//
#include <iostream>
#include <cstdio>
using namespace std;
class Solution {
public:
    bool isSame(TreeNode* l, TreeNode* r){
        if (l == NULL && r == NULL)
            return true;
        if ((l == NULL && r != NULL) || (l != NULL && r == NULL) || (l->val != r->val))
            return false;
        return isSame(l -> left, r -> right) && isSame(l -> right, r -> left);
    }

    bool isSymmetric(TreeNode* root) {
        return isSame(root->left, root->right);
    }
};