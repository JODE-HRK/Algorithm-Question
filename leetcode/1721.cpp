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
    ListNode* swapNodes(ListNode* head, int k) {
        vector<ListNode*> V;
        ListNode* zHead = head;
        while (head != nullptr){
            V.push_back(head);
            head = head -> next;
        }
        int len = V.size();
        swap(V[k-1]->val, V[len - k]->val);
        return zHead;
    }
};