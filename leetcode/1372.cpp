//
// Created by JODE on 2023-04-19.
//
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    int id = 0;
    bool tree[50007];
    int dp[50007][2];
    int dfs(TreeNode* nowNode){
        if(nowNode == nullptr){
            return -1;
        }
        ++id;
        int nowId = id;
        tree[id] = 1;
        dp[id][0] = dp[id][1] = 0;
        int leftId = dfs(nowNode->left);
        int rightId = dfs(nowNode->right);
        if(leftId > 0){
            dp[nowId][0] = dp[leftId][1] + 1;
        }
        if(rightId > 0){
            dp[nowId][1] = dp[rightId][0] + 1;
        }
        ans = max(ans, max(dp[nowId][0], dp[nowId][1]));
        return nowId;
    }
    int longestZigZag(TreeNode* root) {
        fill(tree, tree + 50007, 0);
        dfs(root);
        return ans;
    }
};