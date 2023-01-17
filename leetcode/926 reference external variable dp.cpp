//
// Created by JODE on 2023-01-17.
//
#include <iostream>
using namespace std;
class Solution {
private:
    int dp[100005];
public:
    int minFlipsMonoIncr(string s) {
        dp[0] = 0;
        int cnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '1'){
                dp[i + 1] = dp[i];
                cnt += 1;
            }
            else
                dp[i + 1] = min(dp[i] + 1, cnt);
        }
        return dp[s.size()];
    }
};