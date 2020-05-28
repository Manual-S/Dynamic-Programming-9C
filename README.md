# 简介

🎈 题目为九章算法DP专题中讲到的题目。

🎈 每道题目有好几个程序，这是因为，大部分题目我都是先自己做，然后再对照老师的讲解，修改自己的程序。

🎈 另外吐槽一下lint code的OJ，有一些题目，我的程序写的不对，但是提交也可以通过，所以我建议，同一个题目可以在lint code和leet code上提交两次。


# 第一次课

[669. Coin Change](https://www.lintcode.com/problem/coin-change/description)

- DP解法

  ```c++
  class Solution 
  {
  public:
      int coinChange(vector<int>& coins, int amount) 
      {
          sort(coins.begin(),coins.end());  //不得不忍受一个排序的时间复杂度
          if(amount == 0)
          {
              return 0;
          }
  
          vector<int> dp(amount + 1,INT_MAX);
  
          for(int i = 0;i < coins.size();i++)
          {
              if(coins[i] >= dp.size())
              {
                  continue;
              }
              dp[coins[i]] = 1;
          }
   
          for(int i = coins[0];i < amount + 1;i++)
          {
              if(dp[i] == 1)
              {
                  continue;
              }
  
              //否则
              for(int j = 0;j < coins.size();j++)
              {
                  if(i - coins[j] < 0)
                  {
                      continue;
                  }
  
                  if(dp[i - coins[j]] == INT_MAX)
                  {
                      continue;
                  }
                  dp[i] = std::min(dp[i],dp[i - coins[j]] + 1);
              }
          }
  
          return (dp[amount] == INT_MAX ? -1 : dp[amount]);
      }
  };
  ```

- 老师上课给的DP解法程序

    ```c++
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
            // write your code here
            int len = coins.size();
            
            //因为要计算 dp[0] dp[1]....dp[amount]
            vector<int> dp(amount + 1,INT_MAX);
            dp[0] = 0;
            for(int i = 1;i <= amount;i++)
            {
                for(int j = 0;j < coins.size();j++)
                {
                    if(i >= coins[j] && dp[i - coins[j]] != INT_MAX)
                    {
                        dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
                    }
                }
            }
            
            return dp[amount] == INT_MAX ? -1 : dp[amount];
        }
    };
    ```

  

[114. Unique Paths](https://www.lintcode.com/problem/unique-paths/description)

  - DP解法
  
    ```c++
    class Solution 
    {
    public:
        /**
         * @param m: positive integer (1 <= m <= 100)
         * @param n: positive integer (1 <= n <= 100)
         * @return: An integer
         */
        int uniquePaths(int m, int n) 
        {
            // write your code here
            vector<vector<int>> dp(m,vector<int>(n));
            
            for(int i = 0;i < m;i++)
            {
                for(int j = 0;j < n;j++)
                {
                    if(i == 0 || j == 0)
                    {
                        dp[i][j] = 1;
                        continue;
                    }
                    
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
            
            return dp[m - 1][n - 1];
        }
    };
    ```
  
    

  [116. Jump Game](https://www.lintcode.com/problem/jump-game/my-submissions)

- dfs解法

```C++
class Solution 
{
public:
    /**
     * @param A: A list of integers
     * @return: A boolean
     */
    bool canJump(vector<int> &A) 
    {
        return dfs(A,0);
    }
private:
    bool dfs(vector<int>& A,int start)
    {
        if(start >= A.size() - 1)
        {
            return true;
        }
        
        for(int i = 1;i <= A[start];i++)
        {
            if(dfs(A,start + i))
            {
                return true;
            }
        }
        
        return false;
    }
};
```
[191. Maximum Product Subarray](https://www.lintcode.com/problem/maximum-product-subarray/description)

- DP解法

```c++
  class Solution 
  {
  public:
      /**
       * @param nums: An array of integers
       * @return: An integer
       */
      int maxProduct(vector<int> &nums) 
      {
          int n = nums.size();
          
          vector<int> f(n);
          vector<int> g(n);
          
          f[0] = nums[0];
          g[0] = nums[0];
          
          for(int i = 1;i < n;i++)
          {
              int maxnum = std::max(f[i - 1] * nums[i],g[i - 1] * nums[i]);
              f[i] = std::max(nums[i],maxnum);
              int minnum = std::min(f[i - 1] * nums[i],g[i - 1] * nums[i]);
              g[i] = std::min(nums[i],minnum);
              //cout << i << " " << f[i] << " " << g[i] << endl;
          }
          
          return *std::max_element(f.begin(),f.end());
      }
  };
```

  


# 第二次课

## 坐标型动态规划

  [115. Unique Paths II](https://www.lintcode.com/problem/unique-paths-ii/description)

- DP解法

  ```c++
  class Solution 
  {
  public:
      /**
       * @param obstacleGrid: A list of lists of integers
       * @return: An integer
       */
      int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) 
      {
          // write your code here
          int row  = obstacleGrid.size();
          int col = obstacleGrid[0].size();
          vector<vector<int>> dp(row,vector<int>(col));
          
          bool isrowobstacle = false;
          for(int j = 0;j < col;j++)
          {
              if(obstacleGrid[0][j] == 1)
              {
                  isrowobstacle = true;
              }
              
              if(isrowobstacle)
              {
                  dp[0][j] = 0;
              }
              else
              {
                  dp[0][j] = 1;
              }
          }
          
          bool iscolobstacle = false;
          
          for(int i = 0;i < row;i++)
          {
              if(obstacleGrid[i][0] == 1)
              {
                  iscolobstacle = true;
              }
              
              if(iscolobstacle)
              {
                  dp[i][0] = 0;
              }
              else
              {
                  dp[i][0] = 1;
              }
          }
          
          for(int i = 1;i < row;i++)
          {
              for(int j = 1;j < col;j++)
              {
                  if(obstacleGrid[i][j] == 1)
                  {
                      dp[i][j] = 0;
                      continue;
                  }
                  
                  dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                  
                  //cout << i << " " << j << " " << dp[i][j] << endl;
              }
          }
          
          return dp[row - 1][col - 1];
      }
  };
  ```

- 老师上课写的DP程序

    ```c++
    class Solution {
    public:
        /**
         * @param obstacleGrid: A list of lists of integers
         * @return: An integer
         */
        int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) 
        {
            if(obstacleGrid.empty())
            {
                return true;
            }
            // write your code here
            int row = obstacleGrid.size();
            int col = obstacleGrid[0].size();
            
            vector<vector<int>> dp(row,vector<int>(col));
            
            for(int i = 0;i < row;i++)
            {
                for(int j = 0;j < col;j++)
                {
                    dp[i][j] = 0;
                    if(obstacleGrid[i][j] == 1)
                    {
                        dp[i][j] = 0;
                        //cout << i  << " " << j << " " << dp[i][j] << endl;
                        continue;
                    }
                    
                    if(i == 0 && j == 0)
                    {
                        dp[i][j] = 1;
                        //cout << i  << " " << j << " " << dp[i][j] << endl;
                        continue;
                    }
                    
                    if(i > 0)
                    {
                        dp[i][j] = dp[i][j] + dp[i - 1][j];
                    }
                    
                    if(j > 0)
                    {
                        dp[i][j] = dp[i][j] + dp[i][j - 1];
                    }
                    //cout << i  << " " << j << " " << dp[i][j] << endl;
                }
            }
            
            return dp[row - 1][col - 1];
        }
    };
    ```

    

  [397. Longest Continuous Increasing Subsequence](https://www.lintcode.com/problem/longest-continuous-increasing-subsequence/description)

- DP解法

    ```C++
  class Solution 
  {
  public:
      /**
       * @param A: An array of Integer
       * @return: an integer
       */
      int longestIncreasingContinuousSubsequence(vector<int> &A) 
      {
          if(A.empty())
          {
              return 0;
          }
          // write your code here
          int max1 = getlics(A);
          reverse(A.begin(),A.end());
          int max2 = getlics(A);
          return std::max(max1,max2);
      }
  private:
      int getlics(vector<int>& A)
      {
          int n = A.size();
          vector<int> dp(n,1);
          
          for(int i = 1;i < n;i++)
          {
              if(A[i] > A[i - 1])
              {
                  dp[i] = dp[i - 1] + 1;
              }
          }
          
          return *max_element(dp.begin(),dp.end());
      }
  };
  ```

  

  [110. Minimum Path Sum](https://www.lintcode.com/problem/minimum-path-sum/description)

  - DP解法
  
    ```c++
    class Solution {
    public:
        /**
         * @param grid: a list of lists of integers
         * @return: An integer, minimizes the sum of all numbers along its path
         */
        int minPathSum(vector<vector<int>> &grid) 
        {
            // write your code here
            int row = grid.size();
            int col = grid[0].size();
            
            vector<vector<int>> dp(row,vector<int>(col));
            
            dp[0][0] = grid[0][0];
            
            for(int j = 1;j < col;j++)
            {
                dp[0][j] = dp[0][j - 1] + grid[0][j];
            }
            
            for(int i = 1;i < row;i++)
            {
                dp[i][0] = dp[i - 1][0] + grid[i][0];
            }
            
            for(int i = 1;i < row;i++)
            {
                for(int j = 1;j < col;j++)
                {
                    //dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                    //dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
                    dp[i][j] = std::min(dp[i][j - 1],dp[i - 1][j]) + grid[i][j];
                }
            }
            
            return dp[row - 1][col - 1];
        }
    };
    ```
  
    
  
  [553. Bomb Enemy](https://www.lintcode.com/problem/bomb-enemy/description)
  
  - 暴力解法
  
    ```c++
    class Solution 
    {
    public:
        /**
         * @param grid: Given a 2D grid, each cell is either 'W', 'E' or '0'
         * @return: an integer, the maximum enemies you can kill using one bomb
         */
        int maxKilledEnemies(vector<vector<char>> &grid) 
        {
            if(grid.empty())
            {
                return 0;
            }
            // write your code here
            int row = grid.size();
            int col = grid[0].size();
            int ans = 0;
            
            for(int i = 0;i < row;i++)
            {
                for(int j = 0;j < col;j++)
                {
                    if(grid[i][j] == 'E' || grid[i][j] == 'W')
                    {
                        continue;
                    }
                    
                    ans = std::max(ans,getkillnum(grid,i,j));
                }
            }
            
            return ans;
        }
    private:
        int getkillnum(vector<vector<char>>& grid,int curx,int cury)
        {
            int row = grid.size();
            int col = grid[0].size();
            int dx[] = {-1,1,0,0};
            int dy[] = {0,0,-1,1};  //上下左右四个方向
            int ans = 0;
            
            for(int i = 0;i < 4;i++)
            {
                for(int step = 0;;step++)
                {
                    int nextx = curx + step * dx[i];
                    int nexty = cury + step * dy[i];
                    
                    if(nextx >= row || nexty >= col || nextx < 0 || nexty < 0 || grid[nextx][nexty] == 'W')
                    {
                        //遇到墙或者是边界
                        break;
                    }
                    
                    if(grid[nextx][nexty] == 'E')
                    {
                        ans++;
                    }
                }
            }
            
            return ans;
        }
    };
    ```
  
  - DP解法
  
    ```c++
      class Solution 
      {
      public:
          /**
           * @param grid: Given a 2D grid, each cell is either 'W', 'E' or '0'
           * @return: an integer, the maximum enemies you can kill using one bomb
           */
          int maxKilledEnemies(vector<vector<char>> &grid) 
          {
             if(grid.empty() || grid[0].empty())
             {
                 return 0;
             }
              int row = grid.size();
              int col = grid[0].size();
              
              vector<vector<int>> up(row,vector<int>(col));
              vector<vector<int>> down(row,vector<int>(col));
              vector<vector<int>> left(row,vector<int>(col));
              vector<vector<int>> right(row,vector<int>(col));
              
              //计算up
              for(int j = 0;j < col;j++)
              {
                  if(grid[0][j] == 'E')
                  {
                      up[0][j] = 1;
                  }
                  else
                  {
                      up[0][j] = 0;
                  }
              }
              
              for(int i = 1;i < row;i++)
              {
                  for(int j = 0;j < col;j++)
                  {
                      if(grid[i][j] == 'W')
      				{
      					up[i][j] = 0;
      				}
      				else if(grid[i][j] == 'E')
      				{
      					up[i][j] = up[i - 1][j] + 1;
      				}
      				else if(grid[i][j] == '0')
      				{
      					up[i][j] = up[i - 1][j];
      				}
                  }
              }
      		
      		//计算down
      		for(int j = 0;j < col;j++)
      		{
      			if(grid[row - 1][j] == 'E')
      			{
      				down[row - 1][j] = 1;
      			}
      			else
      			{
      				down[row - 1][j] = 0;
      			}
      		}
      		
      		for(int i = row - 2;i >= 0;i--)
      		{
      			for(int j = 0;j < col;j++)
      			{
      				if(grid[i][j] == 'W')
      				{
      					down[i][j] = 0;
      				}
      				else if(grid[i][j] == 'E')
      				{
      					down[i][j] = down[i + 1][j] + 1;
      				}
      				else if(grid[i][j] == '0')
      				{
      					down[i][j] = down[i + 1][j];
      				}
      			}
      		}
      		
      		//计算left
      		for(int i = 0;i < row;i++)
      		{
      			if(grid[i][col - 1] == 'E')
      			{
      				left[i][col - 1] = 1;
      			}
      			else
      			{
      				left[i][col - 1] = 0;
      			}
      		}
      		
      		for(int i = 0;i < row;i++)
      		{
      			for(int j = col - 2;j >= 0;j--)
      			{
      				if(grid[i][j] == 'W')
      				{
      					left[i][j] = 0;
      				}
      				else if(grid[i][j] == 'E')
      				{
      					left[i][j] = left[i][j + 1] + 1;
      				}
      				else if(grid[i][j] == '0')
      				{
      					left[i][j] = left[i][j + 1];
      				}
      			}
      		}
      		//计算right
      		for(int i = 0;i < row;i++)
      		{
      			if(grid[i][0] == 'E')
      			{
      				right[i][0] = 1;
      			}
      			else
      			{
      				right[i][0] = 0;
      			}
      		}
      		
      		for(int i = 0;i < row;i++)
      		{
      			for(int j = 1;j < col;j++)
      			{
      			    if(grid[i][j] == 'W')
      				{
      					right[i][j] = 0;
      				}
      				else if(grid[i][j] == 'E')
      				{
      					right[i][j] = right[i][j - 1] + 1;
      				}
      				else if(grid[i][j] == '0')
      				{
      					right[i][j] = right[i][j - 1];
      				}
      			}
      		}
      		
      		int ans = 0;
      		
      		for(int i = 0;i < row;i++)
      		{
      			for(int j = 0;j < col;j++)
      			{
      				if(grid[i][j] == 'E' || grid[i][j] == 'W')
      				{
      				    continue;
      				}
      				ans = std::max(ans,up[i][j] + down[i][j] + left[i][j] + right[i][j]);
      			}
      		}
      		
      		return ans;
          }
      };
    ```
  
      
  
  

## 序列型动态规划

  [515. Paint House](https://www.lintcode.com/problem/paint-house/description)

- DP解法

  ```c++
  class Solution 
  {
  public:
      /**
       * @param costs: n x 3 cost matrix
       * @return: An integer, the minimum cost to paint all houses
       */
      int minCost(vector<vector<int>> &costs) 
      {
          if(costs.empty())
          {
              return 0;
          }
          int row = costs.size();
          int col = costs[0].size();
          
          vector<vector<int>> dp(row,vector<int>(col));
          
          for(int j = 0;j < col;j++)
          {
              dp[row - 1][j] = costs[row - 1][j];
          }
          
          for(int i = row - 2;i >= 0;i--)
          {
              for(int j = 0;j < col;j++)
              {
                  if(j == 0)
                  {
                      dp[i][j] = costs[i][j] + std::min(dp[i + 1][j + 1],dp[i + 1][j + 2]);
                  }
                  else if(j == 1)
                  {
                      dp[i][j] = costs[i][j] + std::min(dp[i + 1][j - 1],dp[i + 1][j + 1]);
                  }
                  else if(j == 2)
                  {
                      dp[i][j] = costs[i][j] + std::min(dp[i + 1][j - 1],dp[i + 1][j - 2]);
                  }
                  //cout << dp[i][j] << " ";
              }
              //cout << endl;
          }
          
          
          return *min_element(dp[0].begin(),dp[0].end());
      }
  };
  ```

  

  序列+位操作型动态规划

  [664. Counting Bits](https://www.lintcode.com/problem/counting-bits/description)
  
  ```c++
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
          vector<int> ans(num + 1);
          
          ans[0] = 0;
          
          for(int i = 1;i <= num;i++)
          {
              ans[i] = ans[i >> 1] + i % 2;
          }
          
          return ans;
      }
  };
  ```
  
  

## 划分型动态规划

  [512. Decode Ways](https://www.lintcode.com/problem/decode-ways/description)

- 记忆化递归解法

  ```c++
  class Solution 
  {
  public:
      /**
       * @param s: a string,  encoded message
       * @return: an integer, the number of ways decoding
       */
      int numDecodings(string &s) 
      {
          if(s.empty())
          {
              return 0;
          }
          return dfs(s,0);
      }
  private:
      int dfs(string& s,int start)
      {
          if(start == s.size())
          {
              return 1;
          }
          
          if(m.count(start))
          {
              return m[start];
          }
          
          int ans = 0;
          int num1 = stoi(s.substr(start,1));
          if(num1 == 0)
          {
              return 0;
          }
          if(num1 <= 26 && num1 > 0)
          {
              ans = ans + dfs(s,start + 1);
          }
          if(start + 2 > s.size())
          {
             m[start] = ans;
             return ans; 
          }
          int num2 = stoi(s.substr(start,2));
          if(num2 == 0)
          {
              return 0;
          }
          if(num2 <= 26 && num2 > 0)
          {
              ans = ans + dfs(s,start + 2);
          }
          m[start] = ans;
          return ans;
      }
      
      unordered_map<int,int> m;
  };
  ```

  - DP解法

    ```c++
    class Solution {
    public:
        /**
         * @param s: a string,  encoded message
         * @return: an integer, the number of ways decoding
         */
        int numDecodings(string &s) 
        {
            if(s.empty())
            {
                return 0;
            }
            int n = s.size();
            
            vector<int> dp(n + 1);
            
            dp[n] = 1;  //递归的结束条件
            
            if(s[n - 1] == '0')
            {
                dp[n - 1] = 0;
            }
            else
            {
                dp[n - 1] = 1;
            }
            
            for(int start = n - 2;start >= 0;start--)
            {
                if(s[start] == '0')
                {
                    dp[start] = 0;
                    continue;
                }
                
                dp[start] = dp[start + 1];
            
                int num = stoi(s.substr(start,2));
                
                if(num > 0 && num <= 26)
                {
                    dp[start] = dp[start] + dp[start + 2];
                }
            
            }
            
    
            return dp[0];
        }
    };
    ```

    

------

# 第三次课

  ## 序列型动态规划

[516. Paint House II](https://www.lintcode.com/problem/paint-house-ii/description)

- DP解法 时间复杂度为`O(n * k * k)`其中`n`表示矩阵行数，`k`表示矩阵列数

  这个解法虽然能通过，但是时间复杂度比较高。

  ```c++
  class Solution {
  public:
      /**
       * @param costs: n x k cost matrix
       * @return: an integer, the minimum cost to paint all houses
       */
      int minCostII(vector<vector<int>> &costs) 
      {
          // write your code here
          if(costs.empty())
          {
              return 0;
          }
          int row = costs.size();
          int col = costs[0].size();
          vector<vector<int>> dp(row,vector<int>(col));
          
          for(int j = 0;j < col;j++)
          {
              dp[row - 1][j] = costs[row - 1][j];
          }
          
          int mincost = INT_MAX;
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
                      mincost = std::min(mincost,dp[i + 1][k]);
                  }
                  dp[i][j] = costs[i][j] + mincost;
                  mincost = INT_MAX;
              }
          }
          
          return *min_element(dp[0].begin(),dp[0].end());
      }
  };
  ```

  其实仔细观察程序就能发现，时间复杂度高的原因是，对于每一行，都要花费一个时间复杂度为`O(k)`的去搜索下一行的最小值。现在优化的思路是存储每一行的最小值和次小值。

- 时间复杂度为`O(n * k)`的解法

    ```c++
    class Solution {
    public:
        /**
         * @param costs: n x k cost matrix
         * @return: an integer, the minimum cost to paint all houses
         */
        int minCostII(vector<vector<int>> &costs) 
        {
            // write your code here
            if(costs.empty())
            {
                return 0;
            }
            int row = costs.size();
            int col = costs[0].size();
            vector<vector<int>> dp(row,vector<int>(col));
            
            dp = costs;
            
            int min1 = -1;
            int min2 = -1;
            
            for(int i = 0;i < row;i++)
            {
                int last1 = min1; //下一行的最小值坐标
                int last2 = min2; //下一行的次小值坐标
                min1 = -1;
                min2 = -1;  //记录当前行的最小值和次小值
                for(int j = 0;j < col;j++)
                {
                    if(j != last1)
                    {
                        //当前坐标j并不是下一行的最小值
                        dp[i][j] = dp[i][j] + (last1 < 0 ? 0 : dp[i - 1][last1]); 
                    }
                    else
                    {
                        //很不幸 j坐标就是下一行的最小值 只能加上下一行的次小值
                        dp[i][j] = dp[i][j] + (last2 < 0 ? 0 : dp[i - 1][last2]);
                    }
                    
                    //更新这一行的最小值和次小值
                    if(min1 < 0 || dp[i][j] < dp[i][min1])
                    {
                        //dp[i][j]比当前行的最小值dp[i][min1]还小
                        //那么dp[i][min1]主动让出当前最小值的位置
                        min2 = min1;
                        min1 = j;
                    
                    }
                    else if(min2 < 0 || dp[i][j] < dp[i][min2])
                    {
                        //虽然dp[i][j]不比当前的最小值小
                        //但是比当前的次小值dp[i][min2]小 
                        //那么dp[i][min2]主动让出当前次小值
                        min2 = j;
                    }
                }
            }
            
            //return *min_element(dp[row - 1].begin(),dp[row - 1].end());
            //另一种写法
            return dp[row - 1][min1];
        }
    };
    ```

    

[392. House Robber](https://www.lintcode.com/problem/house-robber/description)

- DP解法

  ```c++
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
          if(A.size() <= 3)
          {
              if(A.size() == 1)
              {
                  return A[0];
              }
              
              if(A.size() == 2)
              {
                  return std::max(A[0],A[1]);
              }
              
              if(A.size() == 3)
              {
                  return std::max(A[1],A[0] + A[2]);
              }
          }
          int len = A.size();
          vector<long long> dp(len);
          dp[len - 1] = A[len - 1];
          dp[len - 2] = A[len - 2];
          dp[len - 3] = dp[len - 1] + A[len - 3];
          
          long long maxnum = 0;
          
          for(int i = len - 4;i >= 0;i--)
          {
              dp[i] = A[i] + std::max(dp[i + 2],dp[i + 3]);
          }
          
          //return *max_element(dp.begin(),dp.end());
          return std::max(dp[0],dp[1]);
      }
  };
  ```

  这个题目和[面试题 17.16. 按摩师](https://leetcode-cn.com/problems/the-masseuse-lcci/)是同样的题目。吐槽一下，我写的程序是真的渣啊。🤷
  
  这个题目的额外空间复杂度可以优化到`O(1)`。
  
- DP解法二 参考老师的程序

  ```c++
  class Solution 
  {
  public:
      /**
       * @param A: An array of non-negative integers
       * @return: The maximum amount of money you can rob tonight
       */
      long long houseRobber(vector<int> &A) 
      {
          int len = A.size();
          
          vector<long long> dp(len);
          
          dp[0] = A[0];
          dp[1] = A[1];
          
          for(int i = 2;i < len;i++)
          {
              dp[i] = std::max(dp[i - 1],dp[i - 2] + A[i]);
          }
          
          return dp[len - 1];
      }
  };
  ```

  - DP解法 将额外空间复杂度优化到`O(1)`👍

    ```c++
    class Solution 
    {
    public:
        /**
         * @param A: An array of non-negative integers
         * @return: The maximum amount of money you can rob tonight
         */
        long long houseRobber(vector<int> &A) 
        {
            if(A.empty())
            {
                return 0;
            }
            
            if(A.size() == 1)
            {
                return A[0];
            }
            int len = A.size();
            
            //vector<long long> dp(len);
            
            //dp[0] = A[0];
            //dp[1] = A[1];
            long long dp0 = A[0];  //i - 2
            long long dp1 = max(A[0],A[1]);
            
            for(int i = 2;i < len;i++)
            {
                //dp[i] = std::max(dp[i - 1],dp[i - 2] + A[i]);
                long long num = std::max(dp1,dp0 + A[i]);
                dp0 = dp1;
                dp1 = num;
            }
            
            return dp1;
        }
    };
    ```

    

[534. House Robber II](https://www.lintcode.com/problem/house-robber-ii/description)

- DP解法1

  ```c++
  class Solution 
  {
  public:
      /**
       * @param nums: An array of non-negative integers.
       * @return: The maximum amount of money you can rob tonight
       */
      int houseRobber2(vector<int> &nums) 
      {
          if(nums.empty())
          {
              return 0;
          }
          if(nums.size() <= 3)
          {
              if(nums.size() == 1)
              {
                  return nums[0];
              }
              
              if(nums.size() == 2)
              {
                  return std::max(nums[0],nums[1]);
              }
              
              if(nums.size() == 3)
              {
                  return *max_element(nums.begin(),nums.end());
              }
          }
          int len = nums.size();
          
          vector<int> robdp(len);  //抢劫
          vector<int> dp(len);  //不抢劫
          
          dp[len - 1] = 0;
          dp[len - 2] = nums[len - 2];
          dp[len - 3] = nums[len - 3];  //不抢劫的情况
          
          robdp[len - 1] = nums[len - 1];
          robdp[len - 2] = nums[len - 2];
          robdp[len - 3] = nums[len - 1] + nums[len - 3];
          
          for(int i = len - 4;i >= 0;i--)
          {
              dp[i] = nums[i] + std::max(dp[i + 2],dp[i + 3]);
              if(i == 0)
              {
                  robdp[i] = 0;
                  continue;
              }
              robdp[i] = nums[i] + std::max(robdp[i + 2],robdp[i + 3]);
              //cout << i << " " << dp[i] << " " << robdp[i] << endl;
          }
          
          int rob = std::max(robdp[1],robdp[2]);
          int nrob = std::max(dp[0],dp[1]);
          
          return std::max(rob,nrob);
      }
  };
  ```

- DP解法二
  
```c++
    class Solution 
    {
    public:
        /**
         * @param nums: An array of non-negative integers.
         * @return: The maximum amount of money you can rob tonight
         */
        int houseRobber2(vector<int> &nums) 
        {
            if(nums.empty())
            {
                return 0;
            }
            int len = nums.size();
            if(len == 1)
            {
                return nums[0];
            }
            return std::max(houseRobber(nums,0,len - 1),houseRobber(nums,1,len));
        }
    private:
        long long houseRobber(vector<int> &A,int start,int end) 
        {
            if(A.empty())
            {
                return 0;
            }
            int len = end - start;  //len 代表长度
            if(len == 1)
            {
                return A[start];
            }
            
            //cout << "len = " << len <<endl;
            long long dp0 = A[start];  //i - 2
            long long dp1 = max(A[start],A[start + 1]);  //i - 1
            
            for(int i = start + 2;i < len + start;i++)
            {
                //dp[i] = std::max(dp[i - 1],dp[i - 2] + A[i]);
                long long num = std::max(dp1,dp0 + A[i]);
                dp0 = dp1;
                dp1 = num;
                //cout << i << " " << num << endl;
            }
            
            return dp1;
        }
    };
```

​    

[149. Best Time to Buy and Sell Stock](https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock/description)

🎈 题目要求只能买卖一次。

```C++
class Solution 
{
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) 
    {
        int len = prices.size();
        vector<vector<int>> dp(len,vector<int>(2));
        
        for(int i = 0;i < len;i++)
        {
            for(int j = 0;j < 2;j++)
            {
                if(i == 0)
                {
                    j == 0 ? dp[0][0] = 0: dp[0][1] = -prices[i];
                    continue;
                }
                if(j == 0)
                {
                    dp[i][j] = std::max(dp[i - 1][0],dp[i - 1][1] + prices[i]); 
                }
                else
                {
                    dp[i][j] = std::max(dp[i - 1][1], -prices[i]);
                }
            }
        }
        
        return dp[len - 1][0];
    }
};
```



[150. Best Time to Buy and Sell Stock II](https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-ii/description)

🎈 可以完成任意次数的交易

```c++
class Solution 
{
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) 
    {
        // write your code here
        if(prices.empty())
        {
            return 0;
        }
        int len = prices.size();
        
        vector<vector<int>> dp(len,vector<int>(2));
        
        for(int i = 0;i < len;i++)
        {
            if(i == 0)
            {
                dp[0][0] = 0;
                dp[0][1] = -prices[0];
                continue;
            }
            dp[i][0] = std::max(dp[i - 1][0],dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][1],dp[i - 1][0] - prices[i]);
        }
        
        return dp[len - 1][0];
    }
};
```



[151. Best Time to Buy and Sell Stock III](https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-iii/description)

🎈 可以完成两次交易

```c++
class Solution 
{
public:
    /**
     * @param prices: Given an integer array
     * @return: Maximum profit
     */
    int maxProfit(vector<int> &prices) 
    {
        // write your code here
        if(prices.empty())
        {
            return 0;
        }
        int len = prices.size();
        vector<vector<vector<int>>> dp(len,vector<vector<int>>(3,vector<int>(2)));
        
        for(int i = 0;i < len;i++)
        {
            for(int k = 2;k >= 1;k--)
            {
                if(i == 0)
                {
                    if(k == 2)
                    {
                        dp[0][2][0] = 0;
                        dp[0][2][1] = 0 - prices[i];
                    }
                    else if(k == 1)
                    {
                        dp[0][1][1] = 0 - prices[i];
                        dp[0][1][0] = 0;
                    }
                    
                    continue;
                }
                dp[i][k][0] = std::max(dp[i - 1][k][0],dp[i - 1][k][1] + prices[i]);
                dp[i][k][1] = std::max(dp[i - 1][k][1],dp[i - 1][k - 1][0] - prices[i]);
                //cout << dp[i][k][0] << " " << dp[i][k][1] << endl;
            }
        }
        return dp[len - 1][2][0];
    }
};
```



[393. Best Time to Buy and Sell Stock IV](https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-iv/description)

🎈 交易次数由函数参数`K`给出。

````c++
class Solution 
{
public:
    /**
     * @param K: An integer
     * @param prices: An integer array
     * @return: Maximum profit
     */
    int maxProfit(int K, vector<int> &prices) 
    {
        // write your code here
        int len = prices.size();
        int ans = 0;
        if(K >= len / 2)
        {
            //无限次的交易
            ans = maxProfitK(prices);
        }
        else
        {
            ans = maxProfitlimitk(prices,K);
        }
        
        return ans;
    }
private:
    //无限制交易次数
    int maxProfitK(vector<int> &prices) 
    {
        // write your code here
        if(prices.empty())
        {
            return 0;
        }
        int len = prices.size();
        
        vector<vector<int>> dp(len,vector<int>(2));
        
        for(int i = 0;i < len;i++)
        {
            if(i == 0)
            {
                dp[0][0] = 0;
                dp[0][1] = -prices[0];
                continue;
            }
            dp[i][0] = std::max(dp[i - 1][0],dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][1],dp[i - 1][0] - prices[i]);
        }
        
        return dp[len - 1][0];
    } 
    
    int maxProfitlimitk(vector<int> &prices,int k)
    {
        int len = prices.size();
    
        vector<vector<vector<int>>> dp(len,vector<vector<int>>(k + 1,vector<int>(2)));
        
        for(int i = 0;i < len;i++)
        {
            for(int j = k;j >= 1;j--)
            {
                if(i == 0)
                {
                    dp[0][j][0] = 0;
                    dp[0][j][1] = -prices[i];
                    continue;
                }
                
                dp[i][j][0] = max(dp[i - 1][j][0],dp[i - 1][j][1] + prices[i]);
                dp[i][j][1] = max(dp[i - 1][j][1],dp[i - 1][j - 1][0] - prices[i]);
            }
        }
        
        return dp[len - 1][k][0];
    }
};
````

再补充两个题目

[1000. Best Time to Buy and Sell Stock with Transaction Fee](https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-with-transaction-fee/description)

🎈 交易次数不限制，但每笔交易要收取交易费

```c++
class Solution 
{
public:
    int maxProfit(vector<int>& prices, int fee) 
    {
        // write your code here
        if(prices.empty())
        {
            return 0;
        }
        int len = prices.size();
        
        vector<vector<int>> dp(len,vector<int>(2));
        
        for(int i = 0;i < len;i++)
        {
            if(i == 0)
            {
                dp[0][0] = 0;
                dp[0][1] = 0 - prices[0] - fee;
                continue;
            }
            dp[i][0] = std::max(dp[i - 1][0],dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][1],dp[i - 1][0] - prices[i] - fee);
        }
        
        return dp[len - 1][0];
    }
};
```

[995. Best Time to Buy and Sell Stock with Cooldown](https://www.lintcode.com/problem/best-time-to-buy-and-sell-stock-with-cooldown/description)

🎈 不限制交易次数 但是含有冷冻期

```c++
class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
    {
        // write your code here
        if(prices.empty())
        {
            return 0;
        }
        int len = prices.size();
        
        vector<vector<int>> dp(len,vector<int>(2));
        
        for(int i = 0;i < len;i++)
        {
            if(i == 0)
            {
                dp[0][0] = 0;
                dp[0][1] = 0 - prices[0];
                continue;
            }
            else if(i == 1)
            {
                //表示没有股票
                dp[1][0] = max(0,prices[1] - prices[0]);
                //表示持有股票
                dp[1][1] = max(-prices[0],-prices[1]);
                continue;
            }
            dp[i][0] = std::max(dp[i - 1][0],dp[i - 1][1] + prices[i]);
            //需要购买的时候 应该从第i - 2天来买
            dp[i][1] = std::max(dp[i - 1][1],dp[i - 2][0] - prices[i]);
        }
        
        return dp[len - 1][0];
    }
};
```



[76. Longest Increasing Subsequence](https://www.lintcode.com/problem/longest-increasing-subsequence/description)

- DP解法 时间复杂度为`O(n * n)`

  ```c++
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
  		if(nums.empty())
  		{
  		    return 0;
  		}
  		int len = nums.size();
  		vector<int> dp(len, 1);
  		dp[0] = 1;
  
  		for (int j = 1; j < len; j++)
  		{
  			for (int i = 0; i < j; i++)
  			{
  				if (nums[i] < nums[j])
  				{
  					dp[j] = std::max(dp[j],dp[i] + 1);
  				}
  			}
  			//cout << j << " " << dp[j] << endl;
  		}
  
  		return *max_element(dp.begin(), dp.end());
  	}
  };
  ```

- DP解法 时间复杂度为`O(nlogn)`

```c++
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
        if(nums.empty())
        {
            return 0;
        }
        int len = 1; //用len记录目前最长上升子序列的长度
        int n = nums.size();
        vector<int> dp(n + 1,0);
        dp[len] = nums[0];
        
        for(int i = 1;i < n;i++)
        {
            if(nums[i] > dp[len])
            {
                len = len + 1;
                dp[len] = nums[i];
            }
            else
            {
                //二分查找
                int left = 1;
                int right = len;
                int pos = 0; //如果找不到 说明所有的数都比nums[i]大 
                            //需要更新dp[1]
                
                while(left <= right)
                {
                    int middle = (left + right) / 2;

                    if(dp[middle] == nums[i])
                    {
                        left = middle;
                        break;
                    }
                    else if(dp[middle] < nums[i])
                    {
                        left = middle + 1;
                    }
                    else if(dp[middle] > nums[i])
                    {
                        right = middle - 1;
                    }
                }
                dp[left] = nums[i];
            }
        }
        
        return len;
    }
};
```



[602. Russian Doll Envelopes](https://www.lintcode.com/problem/russian-doll-envelopes/description)

```c++
bool myfunc(pair<int, int>& a, pair<int, int>& b)
{
	//return a.first < b.first;
	if(a.first != b.first)
	{
	    return a.first < b.first; 
	}
	else
	{
	    return a.second > b.second;
	}
}

class Solution
{
public:
	/*
	 * @param envelopes: a number of envelopes with widths and heights
	 * @return: the maximum number of envelopes
	 */

	int maxEnvelopes(vector<pair<int, int>>& envelopes)
	{
		// write your code here

		sort(envelopes.begin(), envelopes.end(), &myfunc);
        //转化为最长上升子序列
        vector<int> nums;
        for(int i = 0;i < envelopes.size();i++)
        {
            nums.push_back(envelopes[i].second);
        }
        
        return longestIncreasingSubsequence(nums);
	}
private:
    int longestIncreasingSubsequence(vector<int> &nums) 
    {
        // write your code here
        if(nums.empty())
        {
            return 0;
        }
        int len = 1; //用len记录目前最长上升子序列的长度
        int n = nums.size();
        vector<int> dp(n + 1,0);
        dp[len] = nums[0];
        
        for(int i = 1;i < n;i++)
        {
            if(nums[i] > dp[len])
            {
                len = len + 1;
                dp[len] = nums[i];
            }
            else
            {
                //二分查找
                int left = 1;
                int right = len;
                int pos = 0; //如果找不到 说明所有的数都比nums[i]大 
                            //需要更新dp[1]
                
                while(left <= right)
                {
                    int middle = (left + right) / 2;

                    if(dp[middle] == nums[i])
                    {
                        left = middle;
                        break;
                    }
                    else if(dp[middle] < nums[i])
                    {
                        left = middle + 1;
                    }
                    else if(dp[middle] > nums[i])
                    {
                        right = middle - 1;
                    }
                }
                dp[left] = nums[i];
            }
        }
        
        return len;
    }
};
```



------

# 第四次课

## 划分型动态规划

[513. Perfect Squares](https://www.lintcode.com/problem/perfect-squares/description)

🎈 这个题目的解法不唯一，可以使用动态规划，也可以使用BFS。

🎈 比较好玩的是，我的程序可以过leetcode上的OJ，但是lint code上却不可以，卡死在了`1000000000`这个测试用例。

- DP解法 可以过leetcode的OJ，但是不能过lint code的OJ

  ```c++
  class Solution 
  {
  public:
      /**
       * @param n: a positive integer
       * @return: An integer
       */
      int numSquares(int n) 
      {
          // write your code here
          vector<int> dp(n + 1,INT_MAX);
          unordered_set<int> s;
          
          for(int i = 1;i * i <= n;i++)
          {
              s.insert(i * i);
          }
          
          for(int i = 1;i <= n;i++)
          {
              if(s.count(i))
              {
                  dp[i] = 1;
                  continue;
              }
              
              for(auto a : s)
              {
                  if(i < a)
                  {
                      continue;
                  }
                  dp[i] = std::min(dp[i - a] + 1,dp[i]);
              }
              
          }
          
          return dp[n];
          
      }
  };
  ```

  我看了一下提示错误，有可能是容器里放的元素太多了。导致内存不太够了。😥

  错误提示：

  > terminate called after throwing an instance of 'std::bad_alloc' what(): std::bad_alloc Aborted

  下面是我从网上找到的答案：

  > Your memory usage may be on the edge. That is exactly the error given when running out of memory. Try running it again and monitor using ps or top the memory usage.

- 四平方和定理


[108. Palindrome Partitioning II](https://www.lintcode.com/problem/palindrome-partitioning-ii/description)

- 暴力解法

  ```c++
  class Solution
  {
  public:
  	/**
  	 * @param s: A string
  	 * @return: An integer
  	 */
  	int minCut(string &s)
  	{
  		// write your code here
  		if (s.empty())
  		{
  			return 0;
  		}
  
  		return dfs(s, 0);
  	}
  private:
  	int dfs(string& s, int start)
  	{
  		if (ispalindrome(s.substr(start)) || start == s.size() - 1)
  		{
  			return 0;
  		}
  
  		int ans = INT_MAX;
  		int count = 0;
  		for (int i = 0; i < s.size() - start; i++)
  		{
  			string str = s.substr(start, i + 1);
  			if (ispalindrome(str))
  			{
  				count++;
  				count = count + dfs(s, start + i + 1);
  				ans = min(count, ans);
  				count = 0;
  			}
  		}
  
  		return ans;
  	}
  
  	bool ispalindrome(string s)
  	{
  		if (s.empty())
  		{
  			return true;
  		}
  
  		int left = 0;
  		int right = s.size() - 1;
  
  		while (left <= right)
  		{
  			if (s[left] != s[right])
  			{
  				return false;
  			}
  			left++;
  			right--;
  		}
  
  		return true;
  	}
  };
  ```

  暴力尝试的解法大概可以过70%的测试用例，然后意料之中超时。😂

- 记忆化递归

  ```c++
  class Solution
  {
  public:
  	/**
  	 * @param s: A string
  	 * @return: An integer
  	 */
  	int minCut(string &s)
  	{
  		// write your code here
  		if (s.empty())
  		{
  			return 0;
  		}
  
  		return dfs(s, 0);
  	}
  private:
  	int dfs(string& s, int start)
  	{
  		if (ispalindrome(s.substr(start)) || start == s.size() - 1)
  		{
  			return 0;
  		}
          if(m.count(start))
          {
              return m[start];
          }
  		int ans = INT_MAX;
  		int count = 0;
  		for (int i = 0; i < s.size() - start; i++)
  		{
  			string str = s.substr(start, i + 1);
  			if (ispalindrome(str))
  			{
  				count++;
  				count = count + dfs(s, start + i + 1);
  				ans = min(count, ans);
  				count = 0;
  			}
  		}
          m[start] = ans;
  		return ans;
  	}
  
  	bool ispalindrome(string s)
  	{
  		if (s.empty())
  		{
  			return true;
  		}
  
  		int left = 0;
  		int right = s.size() - 1;
  
  		while (left <= right)
  		{
  			if (s[left] != s[right])
  			{
  				return false;
  			}
  			left++;
  			right--;
  		}
  
  		return true;
  	}
  	
  	unordered_map<int,int> m;
  };
  ```

  加了记忆化递归之后，效果还是比较明显的，lint code上可以通过全部的测试用例。leet code上可以通过27个测试用例。👍

- DP解法

[437. Copy Books](https://www.lintcode.com/problem/copy-books/description)

## 博弈型动态规划

[394. Coins in a Line](https://www.lintcode.com/problem/coins-in-a-line/description)

## 背包型动态规划

[92. Backpack](https://www.lintcode.com/problem/backpack/description)

[563. Backpack V](https://www.lintcode.com/problem/backpack-v/description)

[564. Combination Sum IV](https://www.lintcode.com/problem/combination-sum-iv/description)

# 第五次课
# 第六次课
# 第七次课
