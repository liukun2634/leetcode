### 322. 零钱兑换

#### 题目

https://leetcode-cn.com/problems/coin-change/

#### 思路： 动态规划

这一题典型的完全背包问题：

1、 定义状态： dp[i][j] 表示 前i个硬币(coins[0] - coins[i - 1]) 凑成 j 金额的最少硬币数。 ( 0 <= i <= n, 0 <= j <= amount)

2、 状态转移方程: 
- 选择i硬币， 凑成的硬币数为 dp[i][j - coins[i - 1]] + 1 (j >= coins[i - 1])
- 不选择i硬币， 凑成的硬币数为 dp[i - 1][j]

所以 dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1)

3、 初始状态： 
dp[i][j] 默认一开始都为凑不成。因为使用1凑amount最多需要amount，所以dp默认可以设为最大值为amount+1表示一定凑不成的个数。

dp[i][0] 都初始为 0， 表示不需要任何硬币就能达到金额0

4、 处理返回结果：dp[n][amount] 

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        //1. 定义状态, 默认最大值为 amount+1 表示凑不出来
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));
        //2. 初始状态：dp[i][0] 不需要硬币就能凑出来
        for(int i = 0; i <= n; i++){
            dp[i][0] = 0;
        }
        //3. 状态转移
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= amount; j++){
                if(j - coins[i - 1] >= 0){
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        //4. 返回结果
        return dp[n][amount] > amount ? -1 : dp[n][amount];
    }
};
```

**复杂度分析**

时间复杂度：O(mn)
空间复杂度：O(mn)

**优化**

同样，可以使用滚动数组

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        //状态压缩
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= amount; j++){
                if(j - coins[i - 1] >= 0){
                    dp[j] = min(dp[j], dp[j - coins[i - 1]] + 1);
                } 
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
```


#### 思路2： 动态规划 + 不同的定义

dp[i] 定义：当目标金额为 i 时，至少需要 dp[i] 枚硬币凑出。

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        // 外层 for 循环在遍历所有状态的所有取值
        for(int i = 1; i <= amount; i++){
             // 内层 for 循环在求所有选择的最小值
            for(int coin : coins){
                //问题无解，跳过
                if (i - coin < 0) {
                    continue;
                }
                dp[i] = min(dp[i], dp[i - coin] + 1); 
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
```

实际上跟前面状态压缩的解法是一样的，只是交换了i 和 j 的遍历，因为根据不同的定义，从而得出的遍历顺序不同，结果是相同的。