//
// Created by JODE on 2023-01-20.
//
#include <vector>
using namespace std;
class Solution {
private:
    int dp[100005];
public:
    int maxSubArray(vector<int>& nums) {
        int ans = -99999999;
        dp[0] = 0;
        for (int i = 0; i < nums.size(); ++i) {
            ans = max(ans, nums[i]);
        }
        int minn = dp[0];
        for(int i = 0; i < nums.size(); i++){
            dp[i + 1] = dp[i] + nums[i];
            minn = min(minn, dp[i + 1]);
            ans = max(ans, dp[i + 1] - minn);
        }
        return ans;
    }
};