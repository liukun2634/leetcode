### 518. 零钱兑换 II

#### 题目

https://leetcode-cn.com/problems/coin-change-2/

#### 思路：动态规划

这一题典型的完全背包问题：

1、 定义状态： dp[i][j] 表示 前i个硬币(coins[0] - coins[i - 1]) 刚好兑换j的组合数。 ( 0 <= i <= n, 0 <=j <= amount)

2、 状态转移方程: 
- 选择i硬币， 组合数：dp[i][j - coins[i - 1]] (j >= coins[i - 1])
- 不选择i硬币， 组合数：dp[i - 1][j]

所以 dp[i][j] = dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]]

3、 初始状态： dp[i][0] 都初始为 1

4、 处理返回结果：dp[n][amount] 


```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        //1. 定义状态
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
        //2. 初始状态 dp[i][0] 为 1
        for(int i = 0; i <= n; i++){
            dp[i][0] = 1;
        }
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= amount; j++){
                if(j - coins[i - 1] >= 0){
                    dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][amount];
    }
};
```

**复杂度分析**

时间复杂度：O(mn)
空间复杂度：O(mn)

**优化**

这里j需要升序遍历，因为这样每个i就可以达到重复使用的目的。 

```cpp
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        //状态压缩
        vector<int> dp(amount + 1, 0);
        //初始状态
        dp[0] = 1;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= amount; j++){
                if(j - coins[i - 1] >= 0){
                    dp[j] = dp[j] + dp[j - coins[i - 1]];
                }
            }
        }
        return dp[amount];
    }
};
```