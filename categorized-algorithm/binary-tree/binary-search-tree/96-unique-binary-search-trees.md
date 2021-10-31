## 96. 不同的二叉搜索树

### 题目

https://leetcode-cn.com/problems/unique-binary-search-trees/

### 思路： 

dp[i] 是 长度为 i 的， 能够组成的二叉树

遍历根为j，1到n
dp[i] += dp[j - 1] * dp[i - j];

```C++
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i <= n; i++){
            for(int j = 1; j <= i; j++){
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：