#include <vector>
using namespace std;
int g[501][501];
class Solution
{
public:
	int getans(int n)
	{
		int sum = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				sum += g[i][j] > 0 ? (4 * g[i][j] + 2) : 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				if (i - 1 > 0)
					sum -= min(g[i][j], g[i - 1][j]);
				if (i + 1 <= n)
					sum -= min(g[i][j], g[i + 1][j]);
				if (j - 1 > 0)
					sum -= min(g[i][j], g[i][j - 1]);
				if (j + 1 <= n)
					sum -= min(g[i][j], g[i][j + 1]);
			}
		return sum;
	}
	int surfaceArea(vector<vector<int>> &grid)
	{
		int n = grid[0].size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g[i + 1][j + 1] = grid[i][j];
		return getans(n);
	}
};