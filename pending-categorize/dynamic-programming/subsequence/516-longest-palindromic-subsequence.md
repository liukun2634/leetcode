### 516. 最长回文子序列

#### 题目

https://leetcode-cn.com/problems/longest-palindromic-subsequence/

#### 思路： 动态规划

字符串子序列问题，考虑动态规划来解决。

1、定义状态: **dp[i][j] 表示s 以 i 开始，以 j 结尾的子串的最长回文子序列的长度**

2、状态转移方程：

- 如果s[i] == s[j]，需要根据 i 和 j 的位置再判断： 
    - 如果 i == j - 1， 则有 dp[i][j] = 2
    - 如果 i != j - 1， 则有 dp[i][j] = dp[i + 1][j - 1] + 2 (这里其实应该max(dp[i + 1][j], dp[i][j - 1],dp[i + 1][j - 1] + 2), 但最终结果是dp[i + 1][j - 1] + 2, 因为前面两个都是 dp[i + 1][j - 1] + 1)
- 如果s[i] ！= s2[j]，说明 s[i] 和 s[j] 至少有一个不在s[i, j]中的最长回文子串中，所以 dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])

3、初始状态：dp[i][i] = 1 (单个字符串就能组成最小的回文字符串)

4、最终返回结果：res = dp[0][n-1] (假定 s 的长度为 n)


```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        //1. 定义状态: dp[i][j] 表示s 以i开始，以j结尾中的最长回文子序列
        //2. 初始状态：默认都为1，因为一个字符肯定是回文
        vector<vector<int>> dp(n, vector<int>(n, 1));

        //遍历方向跟转移方程状态转移相关
        for(int i = n - 1; i >= 0; i--) {
            for(int j = i + 1; j < n; j++) {
                //3.状态转移方程
                if(s[i] == s[j]) {
                    //如果i == j - 1 要将初始状态从1修改为2
                    dp[i][j] = i == j - 1 ? 2 : dp[i + 1][j - 1] + 2; 
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        //4. 返回值是从0开始，n-1结束
        return dp[0][n-1];
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n^2)