# 563. Backpack V

- DP解法 空间不优化

```
  class Solution 
  {
  public:
      /**
       * @param nums: an integer array and all positive numbers
       * @param target: An integer
       * @return: An integer
       */
      int backPackV(vector<int> &nums, int target) 
  	{
          // write your code here
  		int n = nums.size();
  		if(n == 0)
  		{
  			return 0;
  		}
  		
  		vector<vector<int>> dp(n + 1,vector<int>(target + 1));
          
  		dp[0][0] = 1;
  		
  		for(int j = 1;j <= target;j++)
  		{
  			dp[0][j] = 0;
  		}
  		
  		for(int i = 0;i <= n;i++)
  		{
  			dp[i][0] = 1;
  		}
  		
  		for(int i = 1;i <= n;i++)
  		{
  			for(int j = 1;j <= target;j++)
  			{
  			    dp[i][j] = dp[i - 1][j];
  				
  				if(j >= nums[i - 1])
  				{
  					dp[i][j] = dp[i][j] + dp[i - 1][j - nums[i - 1]];
  				} 
  			}
  		}
  		
  		
  		return dp[n][target];
      }
  	
  };
```

  - DP解法 空间优化 

    优化思路为上课老师讲到的思路，只用一个数组。

```
    class Solution 
    {
    public:
        /**
         * @param nums: an integer array and all positive numbers
         * @param target: An integer
         * @return: An integer
         */
        int backPackV(vector<int> &nums, int target) 
    	{
            // write your code here
    		int n = nums.size();
    		if(n == 0)
    		{
    			return 0;
    		}
    		
    		//vector<vector<int>> dp(n + 1,vector<int>(target + 1));
            
    		vector<int> dp(target + 1);
    		dp[0] = 1;
    		
    		for(int j = 1;j <= target;j++)
    		{
    			dp[j] = 0;
    		}
    		
    		for(int i = 1;i <= n;i++)
    		{
    			for(int j = target;j >= 0;j--)
    			{
    				if(j >= nums[i - 1])
    				{
    					//得出新的dp[j] 并且覆盖掉
    					dp[j] = dp[j] + dp[j - nums[i - 1]];
    				}
    			}
    		}
    		//dp[0][0] = 1;
    		/*
    		for(int j = 1;j <= target;j++)
    		{
    			dp[0][j] = 0;
    		}
    		*/
    		/*
    		for(int i = 0;i <= n;i++)
    		{
    			dp[i][0] = 1;
    		}
    		*/
    		/*
    		for(int i = 1;i <= n;i++)
    		{
    			for(int j = 1;j <= target;j++)
    			{
    			    dp[i][j] = dp[i - 1][j];
    				
    				if(j >= nums[i - 1])
    				{
    					dp[i][j] = dp[i][j] + dp[i - 1][j - nums[i - 1]];
    				} 
    			}
    		}
    		*/
    		
    		return dp[target];
        }
    	
    };
```

    
