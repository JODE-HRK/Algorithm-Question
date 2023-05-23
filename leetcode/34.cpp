//
// Created by JODE on 2023-05-23.
//
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l=0, r=nums.size() - 1;
        int ansl = -1, ansr = -1;
        while (l <= r){
            int mid = (l + r) >> 1;
            if(nums[mid] >= target){
                if(target == nums[mid])
                    ansl = mid;
                cout<<ansl << " " <<endl;
                r = mid - 1;
            }
            else{
                l = mid + 1;
            }
        }

        cout<<endl;

        l=0, r=nums.size() - 1;
        while (l <= r){
            int mid = (l + r) >> 1;
            if(nums[mid] <= target){
                if(target == nums[mid])
                    ansr = mid;
                cout<<ansr << " " <<endl;
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        vector<int> ans;
        ans.push_back(ansl);
        ans.push_back(ansr);
        return ans;
    }
};