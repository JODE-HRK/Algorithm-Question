//
// Created by JODE on 2023-05-26.
//
class Solution {
private:
    int dp[101][210], len;
public:

    int dfs(vector<int>& piles, int start, int M, int totalLeast){
        if(dp[start][M] != -1)
            return dp[start][M];
        int res = 0, taken = 0;
        for(int i = start; i < min(start + 2 * M, len); ++i){
            taken += piles[i];
            res = max(res, totalLeast - dfs(piles, i + 1, max(i - start + 1, M), totalLeast - taken));
        }
        return res;
    }

    int stoneGameII(vector<int>& piles) {
        len = piles.size();
        memset(dp, -1, sizeof(dp));
        return dfs(piles, 0, 1, accumulate(piles.begin(), piles.end(), 0));
    }
};