- DP思路

自己写的DP思路,并不是老师上课写的程序，所以多少会有出入，可以通过OJ。

```
class Solution 
{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
	{
        int m = obstacleGrid.size();  //m行
		int n = obstacleGrid[0].size();  //n列
		
		vector<vector<unsigned int>> dp(m,vector<unsigned int>(n));
		dp[0][0] = 1;
		
		if(m == 1 && n != 1)
		{
			//一行
			for(int j = 0;j < n;j++)
			{
				if(obstacleGrid[0][j] == 1)
				{
					return 0;
				}
			}
			return 1;
		}
		if(m != 1 && n == 1)
		{
			//一列
			for(int i = 0;i < m;i++)
			{
				if(obstacleGrid[i][0] == 1)
				{
					return 0;
				}
			}
			return 1;
		}
		
		//边界的初始化
		for(int i = 0;i < m;i++)
		{
			if(obstacleGrid[i][0] == 1)
			{
				for(;i < m;i++)
				{
					dp[i][0] = 0;
				}
			}
			else
			{
				dp[i][0] = 1;
			}
			
		}
		
		for(int j = 0;j < n;j++)
		{
			if(obstacleGrid[0][j] == 1)
			{
				for(;j < n;j++)
				{
					dp[0][j] = 0;
				}
			}
			else
			{
				dp[0][j] = 1;
			}
		}
		
		for(int i = 1;i < m;i++)
		{
			for(int j = 1;j < n;j++)
			{
				if(obstacleGrid[i][j] == 1)
				{
				    dp[i][j] = 0;
                    continue;					
				}
				
				if(obstacleGrid[i - 1][j] == 1 && obstacleGrid[i][j - 1] == 1)
				{
					dp[i][j] = 0; 
				}
				else if(obstacleGrid[i - 1][j] == 1 && obstacleGrid[i][j - 1] != 1)
				{
					dp[i][j] = dp[i][j - 1];
				}
				else if(obstacleGrid[i - 1][j] != 1 && obstacleGrid[i][j - 1] == 1)
				{
					dp[i][j] = dp[i - 1][j];
				}
				else
				{
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				}
			}
		}
		
		return dp[m - 1][n - 1];
    }
};
```
