//
// Created by JODE on 2023-03-10.
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
#include <random>
using namespace std;
class Solution {

private:
    ListNode* head;

public:

    Solution(ListNode* head) {

        this->head = head;
    }

    int getRandom() {
        int value, cnt = 0;
        ListNode* tmp = this->head;
        for(int i = 1; tmp != nullptr; i++){
            cnt++;
            if (rand() % cnt == 0)
                value = tmp->val;
            tmp = tmp->next;
        }
        return value;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */