# 564. Combination Sum IV
- 递归 + 记忆

  ```
  class Solution 
  {
  public:
      /**
       * @param nums: an integer array and all positive numbers, no duplicates
       * @param target: An integer
       * @return: An integer
       */
      int backPackVI(vector<int> &nums, int target) 
  	{
          // write your code here
  		return getback(nums,target);
      }
  	
  private:
      int getback(vector<int>& nums,int target)
  	{
  		if(target < 0)
  		{
  			return 0;
  		}
  		
  		if(datamap.count(target))
  		{
  			return datamap[target];
  		}
  		
  		if(target == 0)
  		{
  			return 1;
  		}
  		
  		int n = nums.size();
  	    int result = 0;
  		
  		for(int i = 0;i < n;i++)
  		{
  			result = result + getback(nums,target - nums[i]);
  		}
  		datamap[target] = result;
          return result;		
  	}
  	
  	unordered_map<int,int> datamap;
  };
  ```

  如果只用递归的话，会超时，如测试用例`[1,2,4],32`输出为`39882198`，势必会超时。

- DP解法
```
class Solution {
public:
    /**
     * @param nums: an integer array and all positive numbers, no duplicates
     * @param target: An integer
     * @return: An integer
     */
    int backPackVI(vector<int> &nums, int target) {
        // write your code here
		int n = nums.size();
		if(n == 0)
		{
			return 0;
		}
		
		vector<int> dp(target + 1,0);
		
		dp[0] = 1;
		
		for(int i = 1;i <= target;i++)
		{
			for(int j = 0;j < n;j++)
			{
				if(i >= nums[j])
				{
					dp[i] = dp[i] + dp[i - nums[j]];
				}
			}
		}
		
        return dp[target];
    }
};
```

- 输出一种可行的方案

```
  class Solution {
  public:
      /**
       * @param nums: an integer array and all positive numbers, no duplicates
       * @param target: An integer
       * @return: An integer
       */
      int backPackVI(vector<int> &nums, int target) {
          // write your code here
  		int n = nums.size();
  		if(n == 0)
  		{
  			return 0;
  		}
  		
  		vector<int> dp(target + 1,0);
  		vector<int> pai(target + 1);  //如果dp[i] >= 1,则最后一个数字可以是pai[i]
  		
  		dp[0] = 1;
  		
  		for(int i = 1;i <= target;i++)
  		{
  			for(int j = 0;j < n;j++)
  			{
  				if(i >= nums[j])
  				{
  					dp[i] = dp[i] + dp[i - nums[j]];
  					
  					if(dp[i - nums[j]] > 0)
  					{
  						pai[i] = nums[j];
  					}
  				}
  			}
  		}
  		
  		if(dp[target] > 0)
  		{
  			//拼的出来 则打印一种拼的方式
  			int i = target;
  			
  			cout << i << " = "; 
  			
  			while(i != 0)
  			{
  				cout << pai[i] << " ";
  				i = i - pai[i];
  			}
  			
  		}
  		
          return dp[target];
      }
  };
```

  
