//
// Created by JODE on 2023-05-12.
//
#include "cstdio"
#include "vector"
#include "algorithm"
#include "cstdlib"
#include "iostream"
using namespace std;
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        long long dp[n + 1];
        fill(dp, dp + n + 1, 0);
        for (int i = n - 1; i >= 0 ; --i) {
            long long points = questions[i][0];
            int nxt = questions[i][1];

            int nxtQuestion = min(n, i + nxt + 1);
            dp[i] = max(dp[i + 1], points + dp[nxtQuestion]);
        }
        return dp[0];
    }
};