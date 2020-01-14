# 669. Coin Change

- 暴力递归

  ```
  class Solution
  {
  public:
  	/**
  	 * @param coins: a list of integer
  	 * @param amount: a total amount of money amount
  	 * @return: the fewest number of coins that you need to make up
  	 */
  	int coinChange(vector<int> &coins, int amount)
  	{
  		int result = getcoins(coins, amount);
  		return result == INT_MAX ? -1 : result;
  	}
  private:
  	int getcoins(vector<int>& coins, int amount)
  	{
  		if (amount < 0)
  		{
  			return INT_MAX;
  		}
  		if (amount == 0)
  		{
  			return 0;
  		}
  
  		vector<int>::iterator it = find(coins.begin(), coins.end(), amount);
  		int result = 1;
  		int minresult = INT_MAX;
  
  		if (it != coins.end())
  		{
  			return 1;
  		}
  		else
  		{
  
  			for (int i = 0; i < coins.size(); i++)
  			{
  				if(coins[i] == 0)
  				{
  					continue;
  				}
  				
  				int temp = getcoins(coins, amount - coins[i]);
  				
  				if (temp != INT_MAX)
  				{
  					result = result + temp;
  				}
  				else
  				{
  					continue;
  				}
  				//cout << result << " ";
  				if (result < minresult)
  				{
  					minresult = result;
  				}
  				result = 1;
  			}
  		}
  		return minresult;
  	}
  };
  
  ```

  通过了37%的测试用例，最后提示超时，这也是意料之中的结果。

- 记忆 + 递归

  ```
  class Solution
  {
  public:
      /**
  	 * @param coins: a list of integer
  	 * @param amount: a total amount of money amount
  	 * @return: the fewest number of coins that you need to make up
  	 */
  	int coinChange(vector<int> &coins, int amount)
  	{
  	    int result = getcoins(coins, amount);
  		return result == INT_MAX ? -1 : result;
  	}
  private:
  	int getcoins(vector<int>& coins, int amount)
  	{
  		if (amount < 0)
  		{
  			return INT_MAX;
  		}
  		if (amount == 0)
  		{
  			return 0;
  		}
  		if (dp.count(amount))
  		{
  			return dp[amount];
  		}
  		vector<int>::iterator it = find(coins.begin(), coins.end(), amount);
  		int result = 1;
  		int minresult = INT_MAX;
  
  		if (it != coins.end())
  		{
  			return 1;
  		}
  		else
  		{
  
  			for (int i = 0; i < coins.size(); i++)
  			{
  				if (coins[i] == 0)
  				{
  					continue;
  				}
  				int temp = getcoins(coins, amount - coins[i]);
  				
  				if (temp != INT_MAX)
  				{
  					result = result + temp;
  				}
  				else
  				{
  					continue;
  				}
  				//cout << result << " ";
  				if (result < minresult)
  				{
  					minresult = result;
  				}
  				result = 1;
  			}
  		}
  		
  		dp[amount] = minresult;
  
  		return minresult;
  	}
  
  	unordered_map<int, int> dp;
  };
  ```

  

  记忆 + 递归的解法也比较慢。这里我必须吐槽一下，lint code里有一个测试用例是`[0,1,1,8] 9`居然有0面值的硬币。这个硬币面值为0真的把我笑坏了。

- DP解法

```
class Solution
{
public:
	/**
	 * @param coins: a list of integer
	 * @param amount: a total amount of money amount
	 * @return: the fewest number of coins that you need to make up
	 */
	int coinChange(vector<int> &coins, int amount)
	{
		if (amount <= 0)
		{
			return 0;
		}

		// write your code here
		vector<int> dp(amount + 1, INT_MAX);
		int length = coins.size();

		dp[0] = 0;

		//填充dp数组

		for (int i = 0; i <= amount; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX)
				{
					dp[i] = std::min(dp[i - coins[j]] + 1, dp[i]);
				}

			}
			//cout << "i = " << i << " dp[i] = " << dp[i] << endl;
		}

		return (dp[amount] == INT_MAX ? -1 : dp[amount]);
	}
};
```

这个题目比较简单，其实可以直接看出来DP的状态方程。

