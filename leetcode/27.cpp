//
// Created by JODE on 2023-05-18.
//
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int cnt = 0;
        for(auto x: nums){
            if(x != val){
                nums[cnt++] = x;
            }
        }
        return cnt;
    }
};