/*
空间复杂度为O(n)
通过了67%的测试用例
下面进行空间复杂度的优化
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
