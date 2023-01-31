//
// Created by JODE on 2023-01-31.
//
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
private:
    int len;
public:
    int dfs(vector<pair<int, int>> &player, vector<vector<int>> &dp, int preNode, int nodeIndex){
        if (nodeIndex >= len)
            return 0;
        if (dp[preNode + 1][nodeIndex] != -1)
            return dp[preNode + 1][nodeIndex];
        if (preNode == -1 || player[nodeIndex].second >= player[preNode].second){
            return dp[preNode + 1][nodeIndex] = max(dfs(player, dp, nodeIndex, nodeIndex + 1) + player[nodeIndex].second, dfs(player, dp, preNode, nodeIndex + 1));
        }
        return dp[preNode + 1][nodeIndex] = dfs(player, dp, preNode, nodeIndex + 1);
    }
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        len = scores.size();
        vector<pair<int, int>> player;
        vector<vector<int>> dp(len, vector<int>(len, -1));
        for (int i = 0; i < len; ++i) {
            player.push_back(make_pair(ages[i],scores[i]));
        }
        sort(player.begin(), player.end());
        return dfs(player, dp, -1, 0);
    }
};