- 递归解法

  递归解法当然是超时啦，傻瓜！

```
  class Solution 
  {
  public:
      /**
       * @param A: An array of non-negative integers
       * @return: The maximum amount of money you can rob tonight
       */
      long long houseRobber(vector<int> &A) 
  	{
          // write your code here
          if(A.empty()) return 0;
  		int length = A.size();
  		int result = 0;
  		
  		for(int i = 0;i < length;i++)
  		{
  			int temp = getmoney(A,i);
  			if(temp > result)
  			{
  				result = temp;
  			}
  		}
  		return result; 
      }
  private:
      long long getmoney(vector<int>& A,int i)
  	{
  		if(i == A.size() - 1 || i + 2 > A.size() - 1)
  		{
  			return A[i];
  		}
  		long long result = 0;
  		
  		for(int j = 2;j + i < A.size();j++)
  		{
  			long long temp = getmoney(A,i + j) + A[i];
  			if(temp > result)
  			{
  				result = temp;
  			}
  		}
  		
  		return result;
  	}
  };
```

  

- DP解法

  注意下面这个写法有BUG，测出这个BUG的测试用例为`[814,103,294,295]`

```
  class Solution 
  {
  public:
      /**
       * @param A: An array of non-negative integers
       * @return: The maximum amount of money you can rob tonight
       */
      long long houseRobber(vector<int> &A) 
  	{
          // write your code here
  		if(A.empty())
  		{
  			return 0;
  		}
  		
  		int length = A.size();
  		
  		if(length == 1)
  		{
  			return A[0];
  		}
  		if(length == 2)
  		{
  			return *std::max_element(A.begin(),A.end());
  		}
  		if(length == 3)
  		{
  			return std::max(A[1],A[0] + A[2]);
  		}
  		
  		int max1 = 0;
  		int max2 = 0;  //分别维护一个最大值和一个次大值的坐标
  		
  		vector<long long> dp(length);
  		
  		dp[length - 1] = A[length - 1];
  		
  		dp[length - 2] = A[length - 2];
  		
  		dp[length - 3] = A[length - 3] + A[length - 1];
  		
  		if(dp[length - 3] > dp[length - 2])
  		{
  			max1 = length - 3;
  			max2 = length - 2;
  		}
  		else
  		{
  			max1 = length - 2;
  			max2 = length - 3;
  		}
  			
  		for(int i = length - 4;i >= 0;i--)
  		{
  			if(i + 1 != max1)
  			{
  				dp[i] = A[i] + dp[max1];
  			}
              else
  			{
  				dp[i] = A[i] + dp[max2];
  			}				
  			
  			if(dp[i] > dp[max1])
  			{
  				max2 = max1;
  				max1 = i;
  			}
  			else if(dp[i] > dp[max2])
  			{
  				max2 = i;
  			}
  			cout << "i = " << i << " dp[i] =  " << dp[i] << endl;
  		}
  		
  		return *std::max_element(dp.begin(),dp.end());
      }
  };
```

  上面代码出BUG的原因是:

  ```
  		if(dp[length - 3] > dp[length - 2])
  		{
  			max1 = length - 3;
  			max2 = length - 2;
  		}
  		else
  		{
  			max1 = length - 2;
  			max2 = length - 3;
  		}
  ```

  这里讨论`max1`和`max2`的情况不太对。修改后的代码如下:

  ```
  class Solution 
  {
  public:
      /**
       * @param A: An array of non-negative integers
       * @return: The maximum amount of money you can rob tonight
       */
      long long houseRobber(vector<int> &A) 
  	{
          // write your code here
  		if(A.empty())
  		{
  			return 0;
  		}
  		
  		int length = A.size();
  		
  		if(length == 1)
  		{
  			return A[0];
  		}
  		if(length == 2)
  		{
  			return *std::max_element(A.begin(),A.end());
  		}
  		if(length == 3)
  		{
  			return std::max(A[1],A[0] + A[2]);
  		}
  		
  		int max1 = 0;
  		int max2 = 0;  //分别维护一个最大值和一个次大值的坐标
  		
  		vector<long long> dp(length);
  		
  		dp[length - 1] = A[length - 1];
  		
  		dp[length - 2] = A[length - 2];
  		
  		dp[length - 3] = A[length - 3] + A[length - 1];
  		
  		if(dp[length - 3] > dp[length - 2])
  		{
  			max1 = length - 3;
              if(dp[length - 1] > dp[length - 2])
  			{
  				max2 = length - 1;
  			}
  			else
  			{
  				max2 = length - 2;
  			}
  		}
  		else
  		{
  			max1 = length - 2;
  			max2 = length - 3;
  		}
  			
  		for(int i = length - 4;i >= 0;i--)
  		{
  			if(i + 1 != max1)
  			{
  				dp[i] = A[i] + dp[max1];
  			}
              else
  			{
  				dp[i] = A[i] + dp[max2];
  			}				
  			
  			if(dp[i] > dp[max1])
  			{
  				max2 = max1;
  				max1 = i;
  			}
  			else if(dp[i] > dp[max2])
  			{
  				max2 = i;
  			}
  			//cout << "i = " << i << " dp[i] =  " << dp[i] << endl;
  		}
  		
  		return *std::max_element(dp.begin(),dp.end());
      }
  };
  ```

  最后`return *std::max_element(dp.begin(),dp.end());`可以修改为`return dp[max1];`

- 修改后的DP版代码

```
    class Solution 
    {
    public:
        /**
         * @param A: An array of non-negative integers
         * @return: The maximum amount of money you can rob tonight
         */
        long long houseRobber(vector<int> &A) 
    	{
            // write your code here
    		if(A.empty())
    		{
    			return 0;
    		}
    		
    		int length = A.size();
    		
    		if(length == 1)
    		{
    			return A[0];
    		}
    		if(length == 2)
    		{
    			return *std::max_element(A.begin(),A.end());
    		}
    		if(length == 3)
    		{
    			return std::max(A[1],A[0] + A[2]);
    		}
    		
    		int max1 = 0;
    		int max2 = 0;  //分别维护一个最大值和一个次大值的坐标
    		
    		vector<long long> dp(length);
    		
    		dp[length - 1] = A[length - 1];
    		
    		dp[length - 2] = A[length - 2];
    		
    		dp[length - 3] = A[length - 3] + A[length - 1];
    		
    		if(dp[length - 3] > dp[length - 2])
    		{
    			max1 = length - 3;
                if(dp[length - 1] > dp[length - 2])
    			{
    				max2 = length - 1;
    			}
    			else
    			{
    				max2 = length - 2;
    			}
    		}
    		else
    		{
    			max1 = length - 2;
    			max2 = length - 3;
    		}
    			
    		for(int i = length - 4;i >= 0;i--)
    		{
    			if(i + 1 != max1)
    			{
    				dp[i] = A[i] + dp[max1];
    			}
                else
    			{
    				dp[i] = A[i] + dp[max2];
    			}				
    			
    			if(dp[i] > dp[max1])
    			{
    				max2 = max1;
    				max1 = i;
    			}
    			else if(dp[i] > dp[max2])
    			{
    				max2 = i;
    			}
    			//cout << "i = " << i << " dp[i] =  " << dp[i] << endl;
    		}
    		//cout << dp[max1] << " " << dp[max2];
    		//return *std::max_element(dp.begin(),dp.end());
    		return dp[max1];
        }
    };
```

   - DP解法二 老师上课给出的解法

```
     class Solution 
     {
     public:
         /**
          * @param A: An array of non-negative integers
          * @return: The maximum amount of money you can rob tonight
          */
         long long houseRobber(vector<int> &A)
     	{
             // write your code here
     		if(A.empty())
     		{
     			return 0;
     		}
     		
     		int length = A.size();
     		vector<long long> dp(length + 1);
     		
     		dp[0] = 0;
     		dp[1] = A[0];
     		
     		for(int i = 2;i <= length;i++)
     		{
     			dp[i] = std::max(dp[i - 1],dp[i - 2] + A[i - 1]);
     		}
     		
     		return dp[length];
         }
     };
```

     

     
