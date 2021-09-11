## 64. 最小路径和

### 题目

https://leetcode-cn.com/problems/minimum-path-sum/submissions/

### 思路1：动态规划 

dp[i][j] 是到(i,j)的最短路径和。

```C++
class Solution {
public: 
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for(int i = 1; i < m; i++){
            dp[i][0] = grid[i][0] + dp[i-1][0];
        }
        for(int j = 1; j < n; j++){
            dp[0][j] = grid[0][j] + dp[0][j-1];
        }

        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};
```

滚动数组优化，可以直接顺序遍历：

```C++
class Solution {
public: 
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n);
        dp[0] = grid[0][0];
        for(int j = 1; j < n; j++){
            dp[j] = grid[0][j] + dp[j - 1];
        }
        for(int i = 1; i < m; i++){
            dp[0] = dp[0] + grid[i][0];
            for(int j = 1; j < n; j++){
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
            }
        }
        return dp[n-1];
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：