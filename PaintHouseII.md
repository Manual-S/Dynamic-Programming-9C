- DP解法 

时间复杂度比较高

  ```
class Solution 
{
public:
    /**
     * @param costs: n x k cost matrix
     * @return: an integer, the minimum cost to paint all houses
     */
    int minCostII(vector<vector<int>> &costs) 
	{
        // write your code here
		int row = costs.size();
		if(row == 0)
		{
		    return 0;
		}
		
		int col = costs[0].size();
		if(col == 0)
		{
		    return 0;
		}
		
		vector<vector<int>> dp(row,vector<int>(col));
		
		for(int j = 0;j < col;j++)
		{
			dp[row - 1][j] = costs[row - 1][j];
			//cout << dp[row - 1][j] << " ";
		}
		
		//cout << endl;
		
		int mincosts = INT_MAX;
		for(int i = row - 2;i >= 0;i--)
		{
			for(int j = 0;j < col;j++)
			{
				for(int k = 0;k < col;k++)
				{
					if(k == j)
					{
						continue;
					}
					
					if(mincosts > dp[i + 1][k])
					{
					    //cout << mincosts << " ";
						mincosts = dp[i + 1][k];
					}
				}
				
				dp[i][j] = costs[i][j] + mincosts;
                //cout << dp[i][j] << " ";
                mincosts = INT_MAX;				
			}
			//cout << endl;
		}
		
		int result = dp[0][0];
		
		for(int j = 0;j < col;j++)
		{
		    //cout << dp[0][j] << " ";
			if(dp[0][j] < result)
			{
				result = dp[0][j];
			}
		}
		
		return result;
    }
};
  ```

- DP解法二

该解法满足题意,时间复杂度为 `O(n k)`

```
class Solution
  {
public:
  	/**
  	 * @param costs: n x k cost matrix
  	 * @return: an integer, the minimum cost to paint all houses
  	 */
  	int minCostII(vector<vector<int>> &costs)
  	{
  		// write your code here
  		if (costs.empty() || costs[0].empty())
  		{
  			return 0;
  		}
  
  		int row = costs.size();
  		int col = costs[0].size();
  
  		vector<vector<int>> dp = costs;
  
  		int min1 = -1;
  		int min2 = -1;
  
  		for (int i = 0; i < row; i++)
  		{
  			int last1 = min1;
  			int last2 = min2;  //保存上一行的最小值和次小值
  			min1 = -1;
  			min2 = -1;
  			for (int j = 0; j < col; j++)
  			{
  				if (j != last1)
  				{
  					dp[i][j] = dp[i][j] + (last1 < 0 ? 0 : dp[i - 1][last1]);
  				}
  				else
  				{
  					dp[i][j] = dp[i][j] + (last2 < 0 ? 0 : dp[i - 1][last2]);
  				}
  
  				if (min1 < 0 || dp[i][j] < dp[i][min1])
  				{
  					min2 = min1;
  					min1 = j;
  				}
  				else if (min2 < 0 || dp[i][j] < dp[i][min2])
  				{
  					min2 = j;
  				}
  			}
  		}
  
  		return dp.back()[min1];
  	}
  };
```
  
TO DO:第二种方法可以在空间上进行优化。
  
  
  
  
