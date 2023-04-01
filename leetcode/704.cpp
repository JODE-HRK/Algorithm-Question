//
// Created by JODE on 2023-04-01.
//
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1, mid, ans = -1;
        while(l<=r){
            mid = (l + r) >> 1;
            if(nums[mid] < target)
                l = mid + 1;
            else if(nums[mid] > target)
                r = mid - 1;
            else if(nums[mid] == target){
                ans = mid;
                break;
            }
        }
        return ans;
    }
};