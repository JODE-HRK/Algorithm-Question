//
// Created by JODE on 2023-05-17.
//
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    int pairSum(ListNode* head) {
        vector<int> V;
        while (head != nullptr){
            V.push_back(head->val);
            head = head -> next;
        }
        int len = V.size(), ans = 0;
        for (int i = 0; i < len / 2; ++i) {
            ans = max(ans, V[i] + V[len - i - 1]);
        }
        return ans;
    }
};