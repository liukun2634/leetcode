## 516. 最长回文子序列

### 题目

https://leetcode-cn.com/problems/longest-palindromic-subsequence/

### 思路：动态规划 

**技巧**

```C++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        //dp[i][j] 以 i 开始， 以 j 结尾的最长回文子序列长度
        vector<vector<int>> dp(n, vector<int>(n, 0));

        //初始化状态
        for(int i = 0; i < n; i++){
            dp[i][i] = 1;
        }

        //返回值
        int res = 1;
        for(int j = 1; j < n; j++){
            //注意 i 开始的位置
            for(int i = j - 1; i >= 0; i--){
                if(s[i] == s[j]){
                    if(i + 1 == j) {
                        dp[i][j] = max(dp[i][j], 2);
                    } else {
                        dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 2);
                    }
                } else {
                    dp[i][j] = max({dp[i][j], dp[i + 1][j], dp[i][j - 1]});
                }
                res = max(res, dp[i][j]);
            }       
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：