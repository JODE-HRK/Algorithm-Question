//
// Created by JODE on 2023-05-11.
//
#include "cstdio"
#include "vector"
#include "algorithm"
#include "cstdlib"
#include "iostream"
using namespace std;
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m < n) {
            swap(nums1, nums2);
            swap(m, n);
        }
        vector<int> dp(n + 1);
        dp[0] = 0;
        for (int i=1; i<=m; ++i){
            int pre = 0;
            for (int j = 1; j <=n ; ++j) {
                int cur = dp[j];
                if(nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = pre + 1;
                }
                else{
                    dp[j] = max(dp[j - 1], cur);
                }
                pre = cur;
            }
        }
        return dp[n];
    }
};