//
// Created by JODE on 2023-05-25.
//
class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if(k==0 || n >= maxPts + k)
            return 1.0;
        double dp[n + 1];
        double ans = 0.0, currP = 1.0;
        dp[0] = 1.0;

        for (int i = 1; i <= n ; ++i) {
            dp[i] = currP / maxPts;
            if(i < k)
                currP += dp[i];
            else
                ans += dp[i];

            if(i >= maxPts)
                currP -= dp[i - maxPts];
        }
        return ans;
    }
};