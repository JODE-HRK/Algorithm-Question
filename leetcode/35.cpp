//
// Created by JODE on 2023-05-22.
//
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        nums.push_back(100000);
        for (int i = 0; i < n; ++i) {
            if(nums[i] == target)
                return i;
            else if(nums[i+1] == target)
                return i+1;
            else if(nums[i] < target && target <nums[i+1])
                return i + 1;
        }
        return 0;
    }
};