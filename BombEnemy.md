- DP解法

  下面的思路是老师上课讲的思路：

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
          // write your code here
  		int m = grid.size();
  		int n = grid[0].size(); 
  		
  		vector<vector<int>> dp(m,vector<int>(n));
  		vector<vector<int>> res(m,vector<int>(n));
  		int i = 0;
  		int j = 0;
  		for(i = 0;i < m;i++)
  		{
  			for(j = 0;j < n;j++)
  			{
  				res[0][0] = 0;
  			}
  		}
  		cout << "up = " << endl;
  		//up
  		for(i = 0;i < m;i++)
  		{
  			for(j = 0;j < n;j++)
  			{
  				if(grid[i][j] == 'W')
  				{
  					//是墙 一票否决
  					dp[i][j] = 0;
  				}
  				else
  				{
  					dp[i][j] = 0;
  					
  					if(grid[i][j] == 'E')
  					{
  						/*是敌人*/
  						dp[i][j] = 1;
  					}
  					
  					if(i > 0)
  					{
  						/* 空地 或者是 敌人 */
  						dp[i][j] = dp[i - 1][j] + dp[i][j];
  					}
  				}
  				cout << dp[i][j] << " ";
  				res[i][j] = res[i][j] + dp[i][j];
  			}
  			//res[i][j] = res[i][j] + dp[i][j];
  		}
  		cout << endl;
  		cout << "Down = " << endl;
  		//Down
  		for(i = m - 1;i >= 0;i--)
  		{
  			for(j = 0;j < n;j++)
  			{
  				if(grid[i][j] == 'W')
  				{
  					//是墙
  					dp[i][j] = 0;
  				}
  				else
  				{
  					dp[i][j] = 0;
  					
  					if(grid[i][j] == 'E')
  					{
  						dp[i][j] = 1;
  					}
  					
  					if(i + 1 < m)  //i + 1 < m 表示 i 下面还有一行
  					{
  						dp[i][j] = dp[i + 1][j] + dp[i][j];
  					}
  				}
  				cout << dp[i][j] << " ";
  				res[i][j] = res[i][j] + dp[i][j];
  			}
  			//res[i][j] = res[i][j] + dp[i][j];
  		}
  		cout << endl;
  		//Left
  		cout << "Left = " << endl;
  	    for(i = 0;i < m;i++)
  		{
  			for(j = 0;j < n;j++)
  			{
  				if(grid[i][j] == 'W')
  				{
  					//是墙
  					dp[i][j] = 0;
  				}
  				else
  				{
  					dp[i][j] = 0;
  					
  					if(grid[i][j] == 'E')
  					{
  						dp[i][j] = 1;
  					}
  					
  					if(j > 0)
  					{
  						dp[i][j] = dp[i][j - 1] + dp[i][j];
  					}
  				}
  				//cout << dp[i][j] << " ";
  				res[i][j] = res[i][j] + dp[i][j];
  				//cout << "i j " << res[i][j] << " ";
  			}
  		
  		}
  		//cout << endl;
  		//Right
  		//cout << "Right = " << endl;
  		for(i = 0;i < m;i++)
  		{
  			for(j = n - 1;j >= 0;j--)
  			{
  				if(grid[i][j] == 'W')
  				{
  					//是墙
  					dp[i][j] = 0;
  				}
  				else
  				{
  					dp[i][j] = 0;
  					
  					if(grid[i][j] == 'E')
  					{
  						dp[i][j] = 1;
  					}
  					
  					if(j + 1 < n)
  					{
  						dp[i][j] = dp[i][j + 1] + dp[i][j];
  					}
  				}
  				//cout << "j = " << j << " ";
  			    //cout << dp[i][j] << " ";   
  			    res[i][j] = res[i][j] + dp[i][j];
  			}
  		}
  		
  		int maxresult = 0;
  		
  		for(i = 0;i < m;i++)
  		{
  			for(j = 0;j < n;j++)
  			{
  				if(grid[i][j] == '0')
  				{
  					if(res[i][j] > maxresult)
  					{
  						maxresult = res[i][j];
  					}
  				}
  			}
  		}
  		return maxresult;
      }
  };
```

  
