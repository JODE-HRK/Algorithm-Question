//
// Created by JODE on 2023-01-18.
//
#include <iostream>
#include <vector>
using namespace std;
class Solution {
private:
    int rMax[30004];
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int len = nums.size();
        rMax[len - 1] = nums[len - 1];
        for (int i = len - 2, suffix = nums[len - 1]; i>=0; i--){
            suffix += nums[i];
            rMax[i] = max(rMax[i + 1], suffix);
        }
        int normalAns = nums[0];
        int specialAns = nums[0];
        for (int i = 0, suffix = 0, curMax = 0; i < len; ++i) {
            curMax = max(curMax, 0) + nums[i];
            normalAns = max(normalAns, curMax);
            suffix += nums[i];
            if (i + 1 < len)
                specialAns = max(specialAns, suffix + rMax[i + 1]);
        }
        return max(normalAns, specialAns);
    }
};