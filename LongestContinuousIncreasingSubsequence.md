- 穷举

  时间复杂度比较高，因此不推荐

- 动态规划

    ```
  /*
  空间复杂度为O(n)
  通过了67%的测试用例
  */
  class Solution 
  {
  public:
      /**
       * @param A: An array of Integer
       * @return: an integer
       */
      int longestIncreasingContinuousSubsequence(vector<int> &A) 
  	{
          int length = A.size();
          
          if(length == 0)
          {
              return 0;
          }
          
  		vector<int> lr(length,1);
  		vector<int> rl(length,1);
  		
  		for(int i = 0;i < length - 1;i++)
  		{
  			if(A[i] < A[i + 1])
  			{
  				lr[i + 1] = lr[i] + 1;
  			}
  		}
  		
  		if(A[length - 1] > A[length - 2])
  		{
  			lr[length - 1] = lr[length - 2] + 1;
  		}
  		
  		for(int i = 0;i < length;i++)
  		{
  			if(A[i] > A[i + 1])
  			{
  				rl[i + 1] = rl[i] + 1;
  			}
  		}
  		
  		if(A[length - 1] < A[length - 2])
  		{
  			lr[length - 1] = lr[length - 2] + 1;
  		}
  		
  		return std::max(*std::max_element( rl.begin(),rl.end() ),*std::max_element(lr.begin(),lr.end()) );
      }
  };
    ```
  
  上面的动态规划思路是我自己想的，提交到lint code上只能通过67%的测试用例，估计是空间复杂度太高。
