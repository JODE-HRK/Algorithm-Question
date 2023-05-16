//
// Created by JODE on 2023-05-16.
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
    ListNode* swapPairs(ListNode* head) {
        if(head == nullptr)
            return head;
        if(head -> next == nullptr)
            return head;
        ListNode* totalhead = head;
        ListNode* tmpFirst = head;
        ListNode* tmpSecond = head -> next;
        ListNode* nxtHead = head -> next -> next;

        tmpSecond->next = tmpFirst;
        if(nxtHead == nullptr || nxtHead -> next == nullptr)
            tmpFirst->next = nxtHead;
        else
            tmpFirst->next = nxtHead -> next;
        totalhead = tmpSecond;

        head = nxtHead;
        while (head != nullptr && head->next != nullptr){
            tmpFirst = head;
            tmpSecond = head -> next;
            nxtHead = head -> next -> next;

            tmpSecond->next = tmpFirst;
            if(nxtHead == nullptr || nxtHead -> next == nullptr)
                tmpFirst->next = nxtHead;
            else
                tmpFirst->next = nxtHead -> next;


            head = nxtHead;
        }
        return totalhead;
    }
};