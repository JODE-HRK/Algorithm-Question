class Solution
{
public:
    const int mod = 1000000007;
    int coin[4] = {1, 5, 10, 25};
    int waysToChange(int n)
    {
        int dp[2000001];
        dp[0] = 1;
        for (int j = 0; j < 4; j++)
            for (int i = coin[j]; i <= n; i++)
                dp[i] = (dp[i] + dp[i - coin[j]]) % mod;
        return dp[n];
    }
};