## 583. 两个字符串的删除操作

### 题目

https://leetcode-cn.com/problems/delete-operation-for-two-strings/

### 思路：动态规划 

转换为字符串最大公共子序列问题

dp[i][j] 表示 前 i个 和 前j个 字符串最大的公共子序列最多个数。

```C++
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        //在 i - 1，j - 1 范围内的字符串，相同字符的最多个数
        //最长公共子序列问题
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(word1[i - 1] == word2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else{
                    dp[i][j] =max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return (n - dp[n][m]) + (m - dp[n][m]);
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n^2)