- 记忆化递归

  ```
  class Solution 
  {
  public:
      /**
       * @param num: a non negative integer number
       * @return: an array represent the number of 1's in their binary
       */
      vector<int> countBits(int num) 
  	{
          // write your code here
  		vector<int> result;
  		
  		bitsdata[0] = 0;
  		bitsdata[1] = 1;
  		bitsdata[2] = 1;
  		bitsdata[3] = 2;
  		bitsdata[4] = 1;
  		bitsdata[5] = 2;
  		bitsdata[6] = 2;
  		bitsdata[7] = 3;
  		bitsdata[8] = 1;
  		bitsdata[9] = 2;
  		bitsdata[10] = 2;
  		
  		for(int i = 0;i <= num;i++)
  		{
  			result.push_back(getcountbits(i));
  		}
  		
  		return result;
      }
  private:
      int getcountbits(int num)
  	{
  		if(bitsdata.count(num))
  		{
  			return bitsdata[num];
  		}
  		
  		int temp = getcountbits(num / 2) + getcountbits(num % 2);
  		
          bitsdata[num] = temp;
  		
  		return temp;
  	}
  	
  private:
      unordered_map<int,int> bitsdata;
  };
  ```

  通过了lint code中93%的测试用例，当输入`13000166`时提示`Memory Limit Exceeded`。一般来说一个题目超内存的可能性不大，一般的题目对内存的要求并不是很严格，所以出现超内存的情况还是很少的。但并不是没有，出现超内存时我们需要对自己的程序的空间复杂度进行优化，此处的空间复杂度是与时间复杂度相对应的，你可以在算法导论中查看它具体的定义。避免的方法只能是跟据题目所给出的数据范围，看一看数组开辟的能不能再小一些，或者更改算法以使用更小的内存。

  - 动态规划

    ```
    class Solution 
    {
    public:
        /**
         * @param num: a non negative integer number
         * @return: an array represent the number of 1's in their binary
         */
        vector<int> countBits(int num) 
    	{
            // write your code here
    		vector<int> result(num + 1);
    		
            switch(num)
    		{
    			case 0: 
    			    result[0] = 0; 
    				return result;
    			case 1: 
    			    result[0] = 0; 
    				result[1] = 1;
    				return result;
    			case 2: 
    			    result[0] = 0;
    				result[1] = 1;
    				result[2] = 1;
    				return result;
    			default: break;
    		}
    		
    		result[0] = 0;
    		result[1] = 1;
    		result[2] = 1;
    
    		
    		for(int i = 3;i <= num;i++)
    		{
    			result[i] = result[i / 2] + result[i % 2];
    		}
            
    		return result;
        }
    };
    ```

    - 根据老师上课的思路修改后的DP

   首先转移方程中 `result[i] = result[i / 2] + result[i % 2]`可以直接改为`result[i] = result[i / 2] + i % 2;` 修改后的程序为:
  
  ```
  class Solution 
  {
  public:
      /**
       * @param num: a non negative integer number
       * @return: an array represent the number of 1's in their binary
       */
      vector<int> countBits(int num) 
  	{
          // write your code here
  		vector<int> result(num + 1);
  		
  		result[0] = 0;
  		
  		for(int i = 1;i <= num;i++)
  		{
  			result[i] = result[i >> 1] + i % 2;
  		}
          
  		return result;
      }
  };
  ```
  
  

