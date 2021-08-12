### 1143. 最长公共子序列

#### 题目

https://leetcode-cn.com/problems/longest-common-subsequence/

#### 思路： 动态规划

1、定义状态：**dp[i][j] 是s1[0, i-1]，s2[0, j-1]中的最长公共子序列的长度**

这里我一开始可以理解成s1以i-1结尾，s2以j-1结尾的字符串的最长公共序列的长度，最后还对dp[i][j] 再次遍历求最大值。实际上因为是从0 开始的，dp[n][m]就是最终最大的结果，所以这里无需遍历。但最后遍历求最大值也无妨。

2、状态转移方程：

- 如果s1[i - 1] 与 s2[j - 1]相同， 那么 dp[i][j] = dp[i - 1][j - 1] + 1
- 如果s1[i - 1] 不同 s2[j - 1]，说明s1[i-1] 和 s2[j-1] 至少有一个不在最长公共子序列中，所以 dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

3、初始状态：dp[i][j] = 0  这里使用技巧，通过将i, j 从 0- n-1 变为 0 - n, 使得在dp[i-1][j-1]无需额外判断就能工作，同时将0的默认值也加上了。

4、最终结果：res = dp[n][m]


```cpp
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();
        //1. 定义状态，s1[0, i-1]，s2[0, j-1]中的最长公共子序列的长度
        //2. 初始状态默认为0
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        //i从1开始，可以避免初始状态的判断
        for (int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                //3. 状态转移
                if(s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); 
                }
            }
        }

        //4. 处理结果
        return dp[n][m];
    }
};
```

**复杂度分析**

时间复杂度：O(nm)
空间复杂度：O(nm)