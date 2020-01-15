# 108. Palindrome Partitioning II

- DP解法 超时

```
  class Solution 
  {
  public:
      /*判断一个字符串是否为回文串*/
  	bool isPalin(string str)
  	{
  		int length = str.length();
  		if (length == 1)
  		{
  			return true;
  		}
  		int left = 0;
  		int right = 0;
  		if (length % 2 == 0)
  		{
  			//字符串长度为偶数
  			left = length / 2 - 1;
  			right = length / 2;
  		}
  		else
  		{
  			//字符串长度为奇数
  			left = (length - 1) / 2 - 1;
  			right = (length - 1) / 2 + 1;
  		}
  
  
  		while (1)
  		{
  			if (str[left] == str[right] && left < right)
  			{
  				if (left == 0)
  				{
  					return true;
  				}
  				left--;
  				right++;
  			}
  			else
  			{
  				return false;
  			}
  		}
  	}
  
      /**
       * @param s: A string
       * @return: An integer
       */
      int minCut(string &s) 
  	{
          int length = s.length();
  		
  		if(length == 0)
  		{
  			return -1;
  		}
  		
  		vector<int> dp(length + 1);
  		vector<vector<bool>> ispalin(length,vector<bool>(length));
  		
  		for(int i = 0;i < length;i++)
  		{
  			for(int j = 0;j < length;j++)
  			{
  				ispalin[i][j] = false;
  			}
  		}
  		
  		for (int i = 0;i < length;i++)
  	    {
  		    for (int j = 1;j <= length - i;j++)
  		    {
  			    ispalin[i][i + j - 1] = isPalin(str.substr(i,j));
  			    //cout << ispalin[i][j - 1] << " ";
  		    }
  		    //cout << endl;
  	    }
  		
  		dp[0] = 0;
  		
  		for(int i = 1;i <= length;i++)
  		{
  			dp[i] = INT_MAX;
  			
  			for(int j = 0;j <= i - 1;j++)
  			{
  				if(ispalin[j][i - 1])
  				{
  					dp[i] = std::min(dp[j] + 1,dp[i]);
  				}
  			}
  		}
  		
          return dp[length] - 1;
      }
  };
```

  通过了94%的测试用例。

  - 老师上课给出的解法

```
    class Solution
    {
    public:
    	/**
    	 * @param s: A string
    	 * @return: An integer
    	 */
    	int minCut(string &s)
    	{
    		int length = s.length();
    
    		if (length == 0)
    		{
    			return -1;
    		}
    
    		vector<int> dp(length + 1);
    		//int length = str.length();
    		vector<vector<bool>> ispalin(length, vector<bool>(length));
    		int i, j, t;
    
    		for (t = 0; t < s.length(); t++)
    		{
    			//奇数长度的回文串
    			i = j = t;
    
    			while (i >= 0 && j < length && s[j] == s[i])
    			{
    				ispalin[i][j] = true;
    				--i;
    				++j;
    			}
    
    			//偶数长度的回文串
    			i = t;
    			j = t + 1;
    
    			while (i >= 0 && j < length && s[j] == s[i])
    			{
    				ispalin[i][j] = true;
    				--i;
    				++j;
    			}
    		}
    
    		dp[0] = 0;
    
    		for (int i = 1; i <= length; i++)
    		{
    			dp[i] = INT_MAX;
    
    			for (int j = 0; j <= i - 1; j++)
    			{
    				if (ispalin[j][i - 1])
    				{
    					dp[i] = std::min(dp[j] + 1, dp[i]);
    				}
    			}
    		}
    
    		return dp[length] - 1;
    	}
    };
```

