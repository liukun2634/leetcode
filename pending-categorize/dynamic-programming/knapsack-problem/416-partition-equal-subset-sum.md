### 416. 分割等和子集

#### 题目

https://leetcode-cn.com/problems/partition-equal-subset-sum/

#### 思路： 动态规划

对所有元素先求和得到 sum， 然后可以将问题转换成：

给一个重量为 sum/2 的背包 和 n 个物品，每个物品的重量为 nums[i], 如何物品可以使得重量刚好为 sum/2 ? 这样转换成 0-1 背包问题， 每个物品可以选或者不选，且只有唯一的一个。

1、 定义状态： dp[i][j] 表示 前i个物品(nums[0] - nums[i - 1]) 是否能够(true/ false) 使得重量刚好为 j。 ( 0 <= i <= n, 0 <=j <= sum /2)

2、 状态转移方程: 
- 选择 i 物品 dp[i][j] = dp[i - 1][j - nums[i - 1]] (j >= nums[i - 1])
- 不选择 i 物品 dp[i][j] = dp[i - 1][j]
选择和不选择i，只要有一个为true， 那么 dp[i][j] 就为 true

3、 初始状态： d[i][0] 都是 true。

这点注意，所有前i个都可以不选，这样都能达到 0。这里增加一位是为了初始化状态，二维可以画图来定义初始状态。

4、 处理返回结果：dp[n][sum/2] 


```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        //先求和
        for(int i = 0; i < n; i++){
            sum += nums[i];
        }

        //如果总和不可均分，一定为false
        if(sum % 2 == 1) return false;
        int m = sum / 2;
        //1. 定义状态： dp[i][j] 表示 前i个物品(nums[0] - nums[i - 1]) 是否能够(true/ false) 使得重量刚好为 j
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        //2. 初始状态
        for(int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }
        //3. 状态转移方程
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++){
                if(j - nums[i - 1] >= 0) {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }

            }
        }
        //4. 处理返回结果
        return dp[n][m]; 
    }
};
```

**复杂度分析**

时间复杂度：O(nm)
空间复杂度：O(nm)

**优化**

因为 dp[i] 只与 dp[i-1]相关，所以可以压缩成一维数组，空间复杂度降为O(m)。
压缩时要注意遍历方向，必须基于计算过的结果。这里就需要逆序遍历j，这样可以避免之前加入的i再次被加入，影响最后结果。

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += nums[i];
        }

        if(sum % 2 == 1) return false;
        int m = sum / 2;
        //状态压缩
        vector<bool> dp(vector<bool>(m + 1, false));
        dp[0] = true;
        for(int i = 1; i <= n; i++) {
            //这里逆序遍历j，因为每个数字只能用一次，以免之前的结果影响结果。
            for(int j = m; j >= 0; j--){
                if(j - nums[i - 1] >= 0) {
                    dp[j] = dp[j] || dp[j - nums[i - 1]];
                } 
            }
        }
        return dp[m]; 
    }
};
```