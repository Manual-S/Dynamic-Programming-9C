- DP解法

```
  class Solution
  {
  public:
  	/**
  	 * @param prices: Given an integer array
  	 * @return: Maximum profit
  	 */
  	int maxProfit(vector<int> &A)
  	{
  		if (A.empty())
  		{
  			return 0;
  		}
  
  		int length = A.size();
  
  		vector<vector<int>> dp(length + 1, vector<int>(5 + 1));
  
  		//第0天 阶段1的最大获利 最大获利为0
  		dp[0][1] = 0;
  
  		dp[0][2] = dp[0][3] = dp[0][4] = dp[0][5] = INT_MIN;
  
  		int i = 0;
  		int j = 0;
  
  		for (i = 1; i <= length; i++)
  		{
  			//阶段 1 3 5
  			for (j = 1; j <= 5; j = j + 2)
  			{
  				dp[i][j] = dp[i - 1][j];
  
  				if (i > 1 && j > 1 && dp[i - 1][j - 1] != INT_MIN)
  				{
  					dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + A[i - 1] - A[i - 2]);
  				}
  			}
  
  			//阶段 2 4
  			for (j = 2; j <= 5; j = j + 2)
  			{
  				dp[i][j] = dp[i - 1][j - 1];
  
  				if (i > 1 && dp[i - 1][j] != INT_MIN)
  				{
  					dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + A[i - 1] - A[i - 2]);
  				}
  
  				if (j > 2 && i > 1 && dp[i - 1][j - 2] != INT_MIN)
  				{
  					dp[i][j] = std::max(dp[i - 1][j - 2] + A[i - 1] - A[i - 2], dp[i][j]);
  				}
  			}
  		}
  		return std::max( std::max(dp[length][1], dp[length][3]), dp[length][5] ) ;
  
  	}
  };
```

  这道题还是比较复杂的，即使看了好几遍视频，还是感觉自己不能完全理解。
