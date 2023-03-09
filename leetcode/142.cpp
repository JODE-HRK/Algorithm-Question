/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* walker = head;
        ListNode* runner = head;
        while(runner != nullptr || runner->next != nullptr){
            walker = walker->next;
            runner = runner->next->next;
            if(walker == runner){
                ListNode* ans = head;
                while (ans != walker){
                    ans = ans->next;
                    walker = walker->next;
                }
                return ans;
            }
        }
        return nullptr;
    }
};