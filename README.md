# 简介

🎈 题目为九章算法DP专题中讲到的题目。

🎈 每道题目有好几个程序，这是因为，大部分题目我都是先自己做，然后再对照老师的讲解，修改自己的程序。

🎈 另外吐槽一下lint code的OJ，有一些题目，我的程序写的不对，但是提交也可以通过，所以我建议，同一个题目可以在lint code和leet code上提交两次。


# 第一次课

[669. Coin Change](https://www.lintcode.com/problem/coin-change/description)

> 给出不同面额的硬币以及一个总金额. 写一个方法来计算给出的总金额可以换取的最少的硬币数量. 如果已有硬币的任意组合均无法与总金额面额相等, 那么返回 `-1`.
>
> ### Example
>
> **样例1**
>
> ```c++
> 输入：
> [1, 2, 5]
> 11
> 输出： 3
> 解释： 11 = 5 + 5 + 1
> ```

- DP解法

  🎈 这个是一开始我自己写的程序，写的还是比较差劲。😂

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

> 有一个机器人的位于一个 *m* × *n* 个网格左上角。
>
> 机器人每一时刻只能向下或者向右移动一步。机器人试图达到网格的右下角。
>
> 问有多少条不同的路径？

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

> 给出一个非负整数数组，你最初定位在数组的第一个位置。　　　
>
> 数组中的每个元素代表你在那个位置可以跳跃的最大长度。　　　　
>
> 判断你是否能到达数组的最后一个位置。
>
> ### Example
>
> ***样例 1***
>
> ```c++
> 输入 : [2,3,1,1,4]
> 输出 : true
> ```

- DFS解法

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
🎈 这个题目在lint code上用DFS解法不会超时，但在leet code上这个题目即使用DP解法也会超时，需要用到贪心思想。

[191. Maximum Product Subarray](https://www.lintcode.com/problem/maximum-product-subarray/description)

> 找出一个序列中乘积最大的连续子序列（至少包含一个数）。
>
> ### Example
>
> **样例 1:**
>
> ```c++
> 输入:[2,3,-2,4]
> 输出:6
> ```

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

> 现在考虑网格中有障碍物，那样将会有多少条不同的路径？
>
> 网格中的障碍和空位置分别用 1 和 0 来表示。

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

  > 给定一个整数数组（下标从 0 到 n-1， n 表示整个数组的规模），请找出该数组中的最长上升连续子序列。（最长上升连续子序列可以定义为从右到左或从左到右的序列。）
  >
  > ### Example
  >
  > **样例 1：**
  >
  > ```c++
  > 输入：[5, 4, 2, 1, 3]
  > 输出：4
  > 解释：
  > 给定 [5, 4, 2, 1, 3]，其最长上升连续子序列（LICS）为 [5, 4, 2, 1]，返回 4。
  > ```

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

  > 给定一个只含非负整数的m*n网格，找到一条从左上角到右下角的可以使数字和最小的路径。
  >
  > 
  >
  > ### Example
  >
  > ```c++
  > 样例 1:
  > 	输入:  [[1,3,1],[1,5,1],[4,2,1]]
  > 	输出: 7
  > 	
  > 	样例解释：
  > 	路线为： 1 -> 3 -> 1 -> 1 -> 1。
  > ```
  
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
  
  > 给定一个二维矩阵, 每一个格子可能是一堵墙 `W`,或者 一个敌人 `E` 或者空 `0` (数字 '0'), 返回你可以用一个炸弹杀死的最大敌人数. 炸弹会杀死所有在同一行和同一列没有墙阻隔的敌人。 由于墙比较坚固，所以墙不会被摧毁.
  >
  > ### Example
  >
  > **样例1**
  >
  > ```c++
  > 输入:
  > grid =[
  >      "0E00",
  >      "E0WE",
  >      "0E00"
  > ]
  > 输出: 3
  > 解释:
  > 把炸弹放在 (1,1) 能杀3个敌人
  > ```
  
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
  
    🎈 暴力解法没办法过lint code的OJ。
  
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

  

## 序列+位操作型动态规划

  [664. Counting Bits](https://www.lintcode.com/problem/counting-bits/description)

> 给出一个 **非负** 整数 num，对所有满足 `0 ≤ i ≤ num` 条件的数字 i 均需要计算其二进制表示中数字 1 的个数并以数组的形式返回。
>
> ### Example
>
> **样例1**
>
> ```c++
> 输入： 5
> 输出： [0,1,1,2,1,2]
> 解释：
> 0~5的二进制表示分别是：
> 000
> 001
> 010
> 011
> 100
> 101
> 每个数字中1的个数为： 0,1,1,2,1,2
> ```

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

> 有一个消息包含`A-Z`通过以下规则编码
>
> ```c++
> 'A' -> 1
> 'B' -> 2
> ...
> 'Z' -> 26
> ```
>
> 现在给你一个加密过后的消息，问有几种解码的方式
>
> ### Example
>
> **样例 1:**
>
> ```c++
> 输入: "12"
> 输出: 2
> 解释: 它可以被解码为 AB (1 2) 或 L (12).
> ```

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

# 第四次课

## 划分型动态规划

[513. Perfect Squares](https://www.lintcode.com/problem/perfect-squares/description)

> 给一个正整数 n, 请问最少多少个完全平方数(比如1, 4, 9...)的和等于n。
>
> ### Example
>
> **样例 1:**
>
> ```c++
> 输入: 12
> 输出: 3
> 解释: 4 + 4 + 4
> ```

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

> 给定字符串 `s`, 需要将它分割成一些子串, 使得每个子串都是回文串.
>
> 最少需要分割几次?
>
> ### Example
>
> **样例 1:**
>
> ```c++
> 输入: "a"
> 输出: 0
> 解释: "a" 本身就是回文串, 无需分割
> ```

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
  		int len = s.size();
  
  		vector<int> dp(len, INT_MAX);
  
  		dp[0] = 0;  //只有一个字符串不用分割
  
  		for (int i = 1; i < len; i++)
  		{
  			if (ispalindrome(s, 0, i))
  			{
  				dp[i] = 0;  //[0,i]本身就是回文串 不需要分割
  				continue;
  			}
  
  			for (int j = 0; j < i; j++)
  			{
  				if (ispalindrome(s,j + 1,i))
  				{
  					dp[i] = min(dp[i], dp[j] + 1);
  				}
  			}
  		}
  
  		return dp[len - 1];
  	}
  private:
  	bool ispalindrome(string s, int left, int right)
  	{
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

  这个DP解法在lint code上可以过全部OJ，但是leet code上卡在了最后一个测试用例。😥观察这个程序可以发现`ispalindrome(s,j + 1,i)`每次都要判断一下`[j + 1,i]`是不是回文串，如果能把这个时间省掉就好了。之前leet code有一个题目[5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/)，做一个预处理的动态规划数组，这样可以在`O(1)`的时间复杂度内得到一个字串是不是回文串。

- DP解法 优化版

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
  	    
  	    int n = s.size();
          
          vector<vector<int>> dp1(n,vector<int>(n));
  
          for(int l = 0;l < n;l++)
          {
              for(int i = 0;i + l < n;i++)
              {
                  int j = i + l;
                  if(l == 0)
                  {
                      dp1[i][j] = 1;
                  }
                  else if(l == 1)
                  {
                      dp1[i][j] = (s[i] == s[j]);
                  }
                  else
                  {
                      dp1[i][j] = (dp1[i + 1][j - 1] & s[i] == s[j]);
                  }   
              }
          }
          
  		// write your code here
  		if (s.empty())
  		{
  			return 0;
  		}
  		
  		int len = s.size();
  
  		vector<int> dp(len, INT_MAX);
  
  		dp[0] = 0;  //只有一个字符串不用分割
  
  		for (int i = 1; i < len; i++)
  		{
  			if (dp1[0][i])
  			{
  				dp[i] = 0;  //[0,i]本身就是回文串 不需要分割
  				continue;
  			}
  
  			for (int j = 0; j < i; j++)
  			{
  				if (dp1[j + 1][i])
  				{
  					dp[i] = min(dp[i], dp[j] + 1);
  				}
  			}
  		}
  
  		return dp[len - 1];
  	}
  };
  ```

  

[437. Copy Books](https://www.lintcode.com/problem/copy-books/description)

> 给定 `n` 本书, 第 `i` 本书的页数为 `pages[i]`. 现在有 `k` 个人来复印这些书籍, 而每个人只能复印编号连续的一段的书, 比如一个人可以复印 `pages[0], pages[1], pages[2]`, 但是不可以只复印 `pages[0], pages[2], pages[3]` 而不复印 `pages[1]`.
>
> 所有人复印的速度是一样的, 复印一页需要花费一分钟, 并且所有人同时开始复印. 怎样分配这 `k` 个人的任务, 使得这 `n` 本书能够被尽快复印完?
>
> 返回完成复印任务最少需要的分钟数.
>
> ### Example
>
> **样例 1:**
>
> ```c++
> 输入: pages = [3, 2, 4], k = 2
> 输出: 5
> 解释: 第一个人复印前两本书, 耗时 5 分钟. 第二个人复印第三本书, 耗时 4 分钟.
> ```

```c++
class Solution
{
public:
	/**
	 * @param pages: an array of integers
	 * @param k: An integer
	 * @return: an integer
	 */
	int copyBooks(vector<int> &pages, int K)
	{
		// write your code here
		int n = pages.size();
		if (n == 0)
		{
			return 0;
		}

		vector<vector<int>> dp(K + 1, vector<int>(n + 1));

		dp[0][0] = 0;

		//0个抄写员 抄写1 - n本书
		for (int i = 1; i <= n; i++)
		{
			dp[0][i] = INT_MAX;
		}

		//k个抄写员 抄写0本书
		for (int i = 1; i <= K; i++)
		{
			dp[i][0] = 0;
		}

		int sum = 0;

		for (int k = 1; k <= K; k++)
		{
			for (int i = 1; i <= n; i++)
			{
				dp[k][i] = INT_MAX;
				for (int j = i; j >= 0; j--)
				{
					//int temp = std::max(dp[k - 1][j],sum);

					dp[k][i] = std::min(dp[k][i], std::max(dp[k - 1][j], sum));

					//sum = sum + pages[j];
					if (j > 0)
					{
						sum = sum + pages[j - 1];
					}
				}
				sum = 0;
				//dp[k][i] = minresult;
				//cout << dp[k][i] << " ";
			}
			//cout << endl;
		}

		return dp[K][n];
	}
};
```

😱 今天发现，lint code居然数组下标越界都能过OJ。

## 博弈型动态规划

[394. Coins in a Line](https://www.lintcode.com/problem/coins-in-a-line/description)

## 背包型动态规划

[92. Backpack](https://www.lintcode.com/problem/backpack/description)

> 在n个物品中挑选若干物品装入背包，最多能装多满？假设背包的大小为m，每个物品的大小为A[i]。

```c++
class Solution 
{
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector<int> &A) 
    {
        int len = A.size();
        
        vector<vector<bool>> dp(len + 1,vector<bool>(m + 1));
        dp[0][0] = true;
        
        //初始化
        for(int j = 1;j <= m;j++)
        {
            dp[0][j] = false;
        }
        
        for(int i = 1;i < len;i++)
        {
            dp[i][0] = true;
        }
        
        for(int i = 1;i <= len;i++)
        {
            for(int v = 1;v <= m;v++)
            {
                dp[i][v] = dp[i - 1][v];
                
                if(v >= A[i - 1])
                {
                    dp[i][v] = dp[i][v] || dp[i - 1][v - A[i - 1]];
                }
            }
        }
        
        int ans = 0;
        
        for(int i = m;i >= 0;i--)
        {
            if(dp[len][i])
            {
                ans = i;
                break;
            }
        }
        
        return ans;
        
    }
};
```



[563. Backpack V](https://www.lintcode.com/problem/backpack-v/description)

> 给出 n 个物品, 以及一个数组, `nums[i]` 代表第i个物品的大小, 保证大小均为正数, 正整数 `target` 表示背包的大小, 找到能填满背包的方案数。
> `每一个物品只能使用一次`
>
> ### Example
>
> 给出候选物品集合 `[1,2,3,3,7]` 以及 target `7`
>
> ```c++
> 结果的集合为:
> [7]
> [1,3,3]
> ```
>
> 返回 `2`

```c++
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
        int len = nums.size();
        
        vector<vector<int>> dp(len + 1,vector<int>(target + 1));
        
        //初始化
        for(int j = 1;j <= target;j++)
        {
            dp[0][j] = 0;  //拼不出来
        }
        
        for(int i = 1;i <= len;i++)
        {
            dp[i][0] = 1;
        }
        
        dp[0][0] = 1;
        
        for(int i = 1;i <= len;i++)
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
        
        return dp[len][target];
    }
};
```



[564. Combination Sum IV](https://www.lintcode.com/problem/combination-sum-iv/description)

> 给出一个都是正整数的数组 `nums`，其中没有重复的数。从中找出所有的和为 `target` 的组合个数。
>
> ### Example
>
> **样例1**
>
> ```c++
> 输入: nums = [1, 2, 4] 和 target = 4
> 输出: 6
> 解释:
> 可能的所有组合有：
> [1, 1, 1, 1]
> [1, 1, 2]
> [1, 2, 1]
> [2, 1, 1]
> [2, 2]
> [4]
> ```

- DP解法

  ```C++
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
          int len = nums.size();
          
          vector<int> dp(target + 1,0);
          
          dp[0] = 1;//
          
          for(int i = 1;i <= target;i++)
          {
              for(int j = 0;j < len;j++)
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

  🎈 leet code有一个和这个题目差不多的题目[377. 组合总和 Ⅳ](https://leetcode-cn.com/problems/combination-sum-iv/)。但是[377. 组合总和 Ⅳ](https://leetcode-cn.com/problems/combination-sum-iv/)的范围要求比较大。
  
- leet code 377 DP解法
  
    ```c++
    class Solution 
    {
    public:
        /**
         * @param nums: an integer array and all positive numbers, no duplicates
         * @param target: An integer
         * @return: An integer
         */
        unsigned long long combinationSum4(vector<int> &nums, int target) 
        {
            // write your code here
            int len = nums.size();
            
            vector<unsigned long long> dp(target + 1,0);
            
            dp[0] = 1;//
            
            for(int i = 1;i <= target;i++)
            {
                for(int j = 0;j < len;j++)
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

------

# 第五次课

## 背包动态规划

[125. Backpack II](https://www.lintcode.com/problem/backpack-ii/description)

> 有`n`个物品和一个大小为 `m` 的背包. 给定数组 A 表示每个物品的大小和数组 V 表示每个物品的价值.
>
> 问最多能装入背包的总价值是多大?
>
> 样例 1:
>
> 输入: m = 10, A = [2, 3, 5, 7], V = [1, 5, 2, 4]
> 输出: 9
> 解释: 装入 A[1] 和 A[3] 可以得到最大价值, V[1] + V[3] = 9 

- DP解法 空间复杂度为`O(m * n)`

🎈 非常典型的01背包问题。

```c++
class Solution
{
public:
	/**
	 * @param m: An integer m denotes the size of a backpack
	 * @param A: Given n items with size A[i]
	 * @param V: Given n items with value V[i]
	 * @return: The maximum value
	 */
	int backPackII(int m, vector<int> &A, vector<int> &V)
	{
		// write your code here
		int len = A.size();  //len 表示物品的个数
		int ans = 0;
		vector<vector<int>> dp(len + 1, vector<int>(m + 1));

		//初始化
		for (int j = 0; j <= m; j++)
		{
			dp[0][j] = 0;
		}

		for (int i = 1; i <= len; i++)
		{
			dp[i][0] = 0;
		}
		
		for (int i = 1; i <= len; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				dp[i][j] = dp[i - 1][j];

				if (j >= A[i - 1])
				{
					dp[i][j] = std::max(dp[i][j], dp[i - 1][j - A[i - 1]] + V[i - 1]);
				}
				ans = std::max(ans,dp[i][j]);
				//cout << "i = " << i << " j = " << j << " " << dp[i][j] //<< endl;
			}
		}

		return ans;
	}
};
```

leetcode上有一个相似的题目[416. 分割等和子集](https://leetcode-cn.com/problems/partition-equal-subset-sum/)
- 416分割等和子集DP解法

  ```c++
  class Solution 
  {
  public:
      bool canPartition(vector<int>& nums) 
      {
          int sum = 0;
  
          for(int i : nums)
          {
              sum = sum + i;
          }
  
          if(sum % 2 == 1)
          {
              return false;
          }
  
          int target = sum / 2;
          int len = nums.size();
  
          vector<vector<bool>> dp(len + 1,vector<bool>(target + 1));
  
          //初始化
          for(int j = 1;j <= len;j++)
          {
              dp[0][j] = false;  //0个物品拼不出大于0的重量 
          }
  
          for(int i = 0;i <= len;i++)
          {
              dp[i][0] = true;
          }
  
          for(int i = 1;i <= len;i++)
          {
              for(int j = 1;j <= target;j++)
              {
                  dp[i][j] = dp[i - 1][j];
  
                  if(j == nums[i - 1])
                  {
                      dp[i][j] = true;
                      continue;
                  }
  
                  if(j > nums[i - 1])
                  {
                      dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
                  }
              }
          }
  
          return dp[len][target];
      }
  };
  ```


[LintCode 440: Backpack III]()

🎈 这道题目是会员题，我没办法做。


## 区间动态规划

[667. Longest Palindromic Subsequence](lintcode.com/problem/longest-palindromic-subsequence/description)

🎈 这个题目很经典，leet code上有两个类似的题目

[5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/)

[516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)

注意子序列和子串是不一样的，字串必须是连续的，而子序列可以不用连续。

[5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/)

- DP解法

  ```c++
  class Solution 
  {
  public:
      /**
       * @param s: the maximum length of s is 1000
       * @return: the longest palindromic subsequence's length
       */
      string longestPalindrome(string &s) 
      {
          // write your code here
          if(s.size() < 2)
          {
              return s;
          }
          
          int len = s.size();
          int ansmax = 0;
          int left = 0;
          int right = 0;
          
          vector<vector<bool>> dp(len,vector<bool>(len));
          
          //初始化对角线
          for(int i = 0;i < len;i++)
          {
              dp[i][i] = true;
          }
          
          for(int j = 1;j < len;j++)
          {
              for(int i = 0;i < j;i++)
              {
                  if(s[i] != s[j])
                  {
                      dp[i][j] = false;
                  }
                  else
                  {
                      if(j - i < 3)
                      {
                          dp[i][j] = true;
                      }
                      else
                      {
                          dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]); 
                      }
                  }
                  //cout << "i = " << i << " j = " << j << " " << dp[i][j] << endl;
                  if(dp[i][j] && j - i > ansmax)
                  {
                      left = i;
                      right = j;
                      ansmax = j - i;
                  }
              }
          }
          return s.substr(left,ansmax + 1);
      }
  };
  ```

[516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)

- DP解法

  ```c++
  class Solution {
  public:
      /**
       * @param s: the maximum length of s is 1000
       * @return: the longest palindromic subsequence's length
       */
      int longestPalindromeSubseq(string &s) 
      {
          // write your code here
          if(s.size() < 2)
          {
              return s.size();
          }
          
          int len = s.size();
          
          vector<vector<int>> dp(len,vector<int>(len));
          
          for(int i = 0;i < len;i++)
          {
              dp[i][i] = 1;
          }
          
          for(int i = len - 2;i >= 0;i--)
          {
              for(int j = i + 1;j < len;j++)
              {
                  if(s[i] == s[j])
                  {
                      dp[i][j] = dp[i + 1][j - 1] + 2;
                  }
                  else
                  {
                      dp[i][j] = std::max(dp[i + 1][j],dp[i][j - 1]); 
                  }
              }
          }
          
          return dp[0][len - 1];
      }
  };
  ```

  

[LintCode 396 Coins In A Line III]()
🎈 这个题目也是VIP题。

[430. Scramble String](https://www.lintcode.com/problem/scramble-string/description)

- 暴力递归解法

  ```c++
  class Solution 
  {
  public:
      bool isScramble(string s1, string s2) 
      {
          return dfs(s1,s2);
      }
  private:
      bool dfs(string s1,string s2)
      {
          if(s1.size() != s2.size())
          {
              return false;
          }
          if(freq(s1) != freq(s2))
          {
              return false;
          }
          if(s1 == s2)
          {
              return true;
          }
          int len = s1.size();
          for(int i = 1;i < len;i++)
          {
              bool flag1 = dfs(s1.substr(0,i),s2.substr(0,i)) && dfs(s1.substr(i),s2.substr(i));
              bool flag2 = dfs(s1.substr(0,i),s2.substr(len - i)) && dfs(s1.substr(i),s2.substr(0,len - i));
              if(flag1 || flag2)
              {
                  return true;
              }
          }
  
          return false;
      }
  
      vector<int> freq(string_view s)
      {
          vector<int> f(26);
          for(char c : s)
          {
              ++f[c - 'a'];
          }
          return f;
      }
  };
  ```

  🎈 这里`string_view`的作用和`const string&`的作用相同，是C++17中的新特性。

  🎈 可以参考[【现代C++】性能控的工具箱之string_view](https://segmentfault.com/a/1190000018387368)
  
  

[168. Burst Balloons](https://www.lintcode.com/problem/burst-balloons/description)

# 第六次课

## 双序列型动态规划

[77. Longest Common Subsequence](https://www.lintcode.com/problem/longest-common-subsequence/description)

> 给出两个字符串，找到最长公共子序列(LCS)，返回LCS的长度。
>
> ### Example
>
> ```c++
> 样例 1:
> 	输入:  "ABCD" and "EDCA"
> 	输出:  1
> 	
> 	解释:
> 	LCS 是 'A' 或  'D' 或 'C'
> ```

- DP解法

  定义的状态方程为：`dp[i][j]`为`A[0:i]`和`B[0:j]`最长公共子序列的长度。
  
  ```c++
  class Solution 
  {
  public:
      /**
       * @param A: A string
       * @param B: A string
       * @return: The length of longest common subsequence of A and B
       */
      int longestCommonSubsequence(string &A, string &B) 
      {
          if(A.empty() || B.empty())
          {
              return 0;
          }
          // write your code here
          int len1 = A.size();
          int len2 = B.size();
          
          vector<vector<int>> dp(len2,vector<int>(len1));
          
          //初始化
          bool ismatch1 = false;
          for(int j = 0;j < len1;j++)
          {
              if(ismatch1)
              {
                 dp[0][j] = 1;
                 continue;
              }
              if(B[0] == A[j])
              {
                  dp[0][j] = 1;
                  ismatch1 = true;
              }
          }
          bool ismatch2 = false;
          for(int i = 0;i < len2;i++)
          {
              if(ismatch2)
              {
                  dp[i][0] = 1;
                  continue;
              }
              if(A[0] == B[i])
              {
                  dp[i][0] = 1;
                  ismatch2 = true;
              }
          }
          
          for(int i = 1;i < len2;i++)
          {
              for(int j = 1;j < len1;j++)
              {
                  if(B[i] == A[j])
                  {
                      dp[i][j] = dp[i - 1][j - 1] + 1;
                  }
                  else if(B[i] != A[j])
                  {
                      dp[i][j] = std::max(dp[i - 1][j],dp[i][j - 1]);
                  }
              }
          }
          return dp[len2 - 1][len1 - 1];  
      }
};
  ```
  
  🎈 leet code上与这个题目相同的题目[1143. 最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence/)。
  
  🎈 再次吐槽一下lint code，我第一次提交的时候有一个标志位没置位居然也能提交通过，然后在leet code上直接被一个测试用例拦下来。
  
  - DP解法
  
  🎈 这种定义的状态方程为`dp[i][j]`为`A[0:i - 1]`和`B[0:j - 1]`最长公共子序列。可以看到定义的状态方程不同，初始化的时候也是不一样的。很明显这种定义状态方程写起程序来比较容易。
  
  ```c++
  class Solution 
  {
  public:
      int longestCommonSubsequence(string text1, string text2) 
      {
          int len1 = text1.size();
          int len2 = text2.size();
  
          vector<vector<int>> dp(len1 + 1,vector<int>(len2 + 1));
  
          for(int i = 0;i <= len1;i++)
          {
              for(int j = 0;j <= len2;j++)
              {
                  if(i == 0 || j == 0)
                  {
                      dp[i][j] = 0;
                      continue;
                  }
  
                  if(text1[i - 1] == text2[j - 1])
                  {
                      dp[i][j] = dp[i - 1][j - 1] + 1;
                  }
                  else
                  {
                      dp[i][j] = std::max(dp[i - 1][j],dp[i][j - 1]);
                  }
              }
          }
  
          return dp[len1][len2];
      }
  };
  ```
  
  

[29. Interleaving String](https://www.lintcode.com/problem/interleaving-string/description)

> 给出三个字符串:*s1*、*s2*、*s3*，判断*s3*是否由*s1*和*s2*交叉构成。
>
> ### Example
>
> **样例 1：**
>
> ```c++
> 输入:
> "aabcc"
> "dbbca"
> "aadbbcbcac"
> 输出:
> true
> ```

- DP解法

  ```c++
  class Solution 
  {
  public:
      /**
       * @param s1: A string
       * @param s2: A string
       * @param s3: A string
       * @return: Determine whether s3 is formed by interleaving of s1 and s2
       */
      bool isInterleave(string &s1, string &s2, string &s3) 
      {
          // write your code here
          int len1 = s1.size();
          int len2 = s2.size();
          int len3 = s3.size();
          
          if(len1 + len2 != len3)
          {
              return false;
          }
          
          vector<vector<bool>> dp(len2 + 1,vector<bool>(len1 + 1));
          
          //初始化
          for(int j = 1;j <= len1;j++)
          {
              if(s3[j - 1] != s1[j - 1])
              {
                  //
                  break;
              }
              dp[0][j] = true;
          }
          
          for(int i = 1;i <= len2;i++)
          {
              if(s3[i - 1] != s2[i - 1])
              {
                  break;
                  //
              }
              dp[i][0] = true;
          }
          
          dp[0][0] = true;
          
          for(int i = 1;i <= len2;i++)
          {
              for(int j = 1;j <= len1;j++)
              {
  
                  dp[i][j] = (dp[i][j - 1] && s3[i + j - 1] == s1[j - 1]) || (dp[i - 1][j] && s3[i + j - 1] == s2[i - 1]); 
              }
          }
          
          
          return dp[len2][len1];
      }
  };
  ```

  🎈 leet code上与这个题目相同的题目 [97. 交错字符串](https://leetcode-cn.com/problems/interleaving-string/)。

[119. Edit Distance](https://www.lintcode.com/problem/edit-distance/description)

> 给出两个单词word1和word2，计算出将word1 转换为word2的最少操作次数。
>
> 你总共三种操作方法：
> - 插入一个字符
> - 删除一个字符
> - 替换一个字符
>
> ### Example
>
> **样例 1:**
>
> ```c++
> 输入: 
> "horse"
> "ros"
> 输出: 3
> 解释: 
> horse -> rorse (替换 'h' 为 'r')
> rorse -> rose (删除 'r')
> rose -> ros (删除 'e')
> ```

- DP解法

  ```C++
  class Solution 
  {
  public:
      /**
       * @param word1: A string
       * @param word2: A string
       * @return: The minimum number of steps.
       */
      int minDistance(string &word1, string &word2) 
      {
          // write your code here
          int len1 = word1.size();
          int len2 = word2.size();
          
          vector<vector<int>> dp(len1 + 1,vector<int>(len2 + 1));
          
          //初始化
          for(int j = 0;j <= len2;j++)
          {
              dp[0][j] = j; 
          }
          
          for(int i = 0;i <= len1;i++)
          {
              dp[i][0] = i;
          }
          
          for(int i = 1;i <= len1;i++)
          {
              for(int j = 1;j <= len2;j++)
              {
                  dp[i][j] = std::min(dp[i][j - 1] + 1,std::min(dp[i - 1][j - 1] + 1,dp[i - 1][j] + 1));
                  
                  if(word1[i - 1] == word2[j - 1])
                  {
                      dp[i][j] = std::min(dp[i][j],dp[i - 1][j - 1]);
                  }
              }
          }
          
          return dp[len1][len2];
      }
  };
  ```

  🎈 leet code上相似的题目[72. 编辑距离](https://leetcode-cn.com/problems/edit-distance/)

[118. Distinct Subsequences](https://www.lintcode.com/problem/distinct-subsequences/description)

> 给定字符串 `S` 和 `T`, 计算 `S` 的所有子序列中有多少个 `T`.
>
> 子序列字符串是原始字符串删除一些(或零个)字符之后得到的字符串, 并且要求剩下的字符的相对位置不能改变. (比如 `"ACE"` 是 `ABCDE` 的一个子序列, 而 `"AEC"` 不是)
>
> ### Example
>
> **样例 1:**
>
> ```c++
> 输入: S = "rabbbit", T = "rabbit"
> 输出: 3
> 解释: 你可以删除 S 中的任意一个 'b', 所以一共有 3 种方式得到 T.
> ```

- DP解法

  ```c++
  class Solution 
  {
  public:
      /**
       * @param S: A string
       * @param T: A string
       * @return: Count the number of distinct subsequences
       */
      int numDistinct(string &s, string &t) 
      {
          // write your code here
          int len1 = s.size();
          int len2 = t.size();
          
          vector<vector<unsigned int>> dp(len1 + 1,vector<unsigned int>(len2 + 1));
          
          //初始化
          for(int j = 1;j <= len2;j++)
          {
              dp[0][j] = 0;
          }
          
          for(int i = 0;i <= len1;i++)
          {
              dp[i][0] = 1;
          }
          
          for(int i = 1;i <= len1;i++)
          {
              for(int j = 1;j <= len2;j++)
              {
                  dp[i][j] = dp[i - 1][j];
                  
                  if(s[i - 1] == t[j - 1])
                  {
                      dp[i][j] = dp[i - 1][j - 1] + dp[i][j];
                  }
                  
                  //cout << "i = " << i << " j = " << j << " " << dp[i][j] //<< endl;
              }
          }
          
          return dp[len1][len2];
      }
  };
  ```

  

[154. Regular Expression Matching](https://www.lintcode.com/problem/regular-expression-matching/description)

🎈 正则表达式的匹配

```c++
class Solution 
{
public:
    /**
     * @param s: A string 
     * @param p: A string includes "." and "*"
     * @return: A boolean
     */
    bool isMatch(string &s, string &p) 
    {
        // write your code here
        int len1 = s.size();
        int len2 = p.size();
        
        vector<vector<bool>> dp(len1 + 1,vector<bool>(len2 + 1));
        
        for(int i = 0;i <= len1;i++)
        {
            for(int j = 0;j <= len2;j++)
            {
                if(i == 0 && j == 0)
                {
                    dp[i][j] = true;
                    continue;
                }
                
                if(j == 0)
                {
                    dp[i][j] = false;
                    continue;
                }
                
                dp[i][j] = false;
                
                if(p[j - 1] != '*')
                {
                    if(i > 0 && (p[j - 1] == '.' || s[i - 1] == p[j - 1]))
                    {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                    
                }
                else 
                {
                    if(j > 1)
                    {
                        dp[i][j] = dp[i][j] || dp[i][j - 2];
                    }
                    
                    if(i > 0 && j > 1)
                    {
                        if(p[j - 2] == '.' || p[j - 2] == s[i - 1])
                        {
                            dp[i][j] = dp[i][j] || dp[i - 1][j];
                        }
                    }
                }
                //cout << "i = " << i  << " j = " << j << " " << //dp[i][j] << endl;
            }
        }
        
        return dp[len1][len2];
    }
};
```

🎈 第一遍做这个题的时候，我是参考了老师的代码，自己不是很明白，下面是我第二次做的时候代码，首先应该判断`s`和`p`是否合法，尤其是对于`p`中，`*`不可以作为第一个字符，`*`的前一个不能是`*`。第二次做的代码虽然不如老师的简洁，但是可读性比较好。

- 第二次做代码

  ```c++
  class Solution 
  {
  public:
      bool isMatch(string s, string p) 
      {
          int len1 = s.size();
          int len2 = p.size();
          if(!isvalid(s,p))
          {
              return false;
          }
          vector<vector<bool>> dp(len1 + 1,vector<bool>(len2 + 1));
              
          //初始化
          dp[0][0] = true;
  
          for(int i = 1;i <= len1;i++)
          {
              dp[i][0] = false;
          }
  
          for(int j = 1;j <= len2;j++)
          {
              dp[0][j] = false;
  
              if(p[j - 1] == '*' && dp[0][j - 2])
              {
                  dp[0][j] = true;
              }
          }
  
          for(int i = 1;i <= len1;i++)
          {
              for(int j = 1;j <= len2;j++)
              {
                  dp[i][j] = false;
  
                  if(s[i - 1] == p[j - 1] || p[j - 1] == '.')
                  {
                      dp[i][j] = dp[i - 1][j - 1];
                  }
                  else if(p[j - 1] == '*')
                  {
                      if(j >= 2)
                      {
                          dp[i][j] = dp[i][j - 2];
  
                          if(p[j - 2] == '.' || p[j - 2] == s[i - 1])
                          {
                              dp[i][j] = dp[i][j] || dp[i - 1][j];
                          }
                      }
                  }
              }
          }
          return dp[len1][len2];
      }
  private:
      bool isvalid(string& s,string& p)
      {
          for(int i = 0;i < p.size();i++)
          {
              if(p[i] == '*' && (i == 0 || (p[i - 1] == '*')))
              {
                  return false;
              }
          }
          
          return true;
      }
  };
  
  ```

  

[192. Wildcaird Matching](https://www.lintcode.com/problem/wildcard-matching/description)

🎈 通配符的匹配🤷

- DP解法

```c++
class Solution 
{
public:
    /**
     * @param s: A string 
     * @param p: A string includes "?" and "*"
     * @return: is Match?
     */
    bool isMatch(string &s, string &p) 
    {
        // write your code here
        int len1 = s.size();
        int len2 = p.size();
        
        vector<vector<bool>> dp(len1 + 1,vector<bool>(len2 + 1));
        
        for(int i = 0;i <= len1;i++)
        {
            for(int j = 0;j <= len2;j++)
            {
                if(i == 0 && j == 0)
                {
                    dp[i][j] = true;  //空串和空的通配符匹配
                    continue;
                }
                
                if(j == 0)
                {
                    dp[i][j] = false;  //空的通配符不能匹配大于0的串
                    continue;
                }
                
                
                dp[i][j] = false;
                
                if(p[j - 1] != '*')
                {
                    if(i > 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '?'))
                    {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                }
                else 
                {
                    dp[i][j] = dp[i][j - 1];
                    if(i > 0)
                    {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
                //cout << "i = " << i << " j = " << j << " " << dp[i][j] << endl;
            }
        }
        
        return dp[len1][len2];
    }
};
```



[668. Ones and Zeroes](https://www.lintcode.com/problem/ones-and-zeroes/description)



# 第七次课
