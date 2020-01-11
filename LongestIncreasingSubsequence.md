# 76. Longest Increasing Subsequence

- 递归解法1

  这个递归解法是我自己写的，不出意外在lint code上提交超时。

```
  class Solution 
  {
  public:
      /**
       * @param nums: An integer array
       * @return: The length of LIS (longest increasing subsequence)
       */
      int longestIncreasingSubsequence(vector<int> &nums) 
  	{
          // write your code here
  		int n = nums.size();
  		if(n == 0)
  		{
  			return 0;
  		}
  		int ans = 1;
  		
  		for(int i = n - 1;i >= 0;i--)
  		{
  			ans = std::max(ans,LIS(nums,i));
  		}
  		
  		return ans;
      }
  private:
      int LIS(const vector<int>& nums,int r)
  	{
  		if(r == 0)
  		{
  			return 1;
  		}
  		
  		int ans = 1;
  		
  		for(int i = r - 1;i >= 0;i--)
  		{
  			if(nums[r] > nums[i])
  			{
  				ans = std::max(ans,LIS(nums,i) + 1);
  			}
  		}
  		
  		return ans;
  	}
  };
```

  上面的递归超时，那么接下来的优化思路是采用记忆化递归。

- 递归解法2

以下解法参考了[花花酱 LeetCode 300. Longest Increasing Subsequence](http://zxi.mytechroad.com/blog/dynamic-programming/leetcode-300-longest-increasing-subsequence/),其中`dp[r]`存储了`r`位置的最长递增子序列。

```
class Solution 
{
public:
    /**
     * @param nums: An integer array
     * @return: The length of LIS (longest increasing subsequence)
     */
    int longestIncreasingSubsequence(vector<int> &nums) 
	{
        // write your code here
		int n = nums.size();
		if(n == 0)
		{
			return 0;
		}
		int ans = 1;
		
		dp = vector<int>(n,0);
		
		for(int i = n - 1;i >= 0;i--)
		{
			ans = std::max(ans,LIS(nums,i));
		}
		
		return ans;
    }
private:
    int LIS(const vector<int>& nums,int r)
	{
		if(r == 0)
		{
			return 1;
		}
		
		if(dp[r] > 0)
		{
			return dp[r];
		}
		
		int ans = 1;
		
		for(int i = r - 1;i >= 0;i--)
		{
			if(nums[r] > nums[i])
			{
				ans = std::max(ans,LIS(nums,i) + 1);
			}
		}
		
		dp[r] = ans;
		
		return ans;
	}
	
	vector<int> dp;
};
```

记忆化递归可以将时间复杂度降低到`O(N ^ 2)`。

- 动态规划算法

```
  class Solution 
  {
  public:
      /**
       * @param nums: An integer array
       * @return: The length of LIS (longest increasing subsequence)
       */
      int longestIncreasingSubsequence(vector<int> &nums) 
  	{
          // write your code here
  		int n = nums.size();
  		if(n == 0)
  		{
  			return 0;
  		}
  		
  		vector<int> dp(n,1);
  		
  		dp[0] = 1;
  		
  		for(int i = 1;i < n;i++)
  		{
  			for(int j = i - 1;j >= 0;j--)
  			{
  				if(nums[i] > nums[j])
  				{
  					dp[i] = std::max(dp[j] + 1,dp[i]);
  				}
  			}
  		}
  		
  		return *std::max_element(dp.begin(),dp.end());
      }
  };
```

  

- TO DO

  补充时间复杂度为`Nlog(N)`的解法

