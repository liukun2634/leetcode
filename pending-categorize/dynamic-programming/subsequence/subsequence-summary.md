### 序列dp

子串是连续的， 但子序列不一定连续。

- 对于子串问题，考虑滑动窗口
- 对于子序列问题，考虑用动态规划。（当然子串也可以使用, 比如53.最大子序和 则不能用滑动窗口，而需要动态规划）


#### 数组中子序列

经典题：最长递增子序列（LIS）

数组子序列经常使用的dp[i]定义是 **以 nums[i] 为结尾的** 子序列的最值 

**数组模板**：

1、定义状态：dp[i] 指的是**以 nums[i] 为结尾的**子序列的最值

2、初始状态 

3、状态转移方程: 能够带入nums[i]，将dp[j] (j < i) 转换为 dp[i]。

4、处理最终结果: 一般要再次遍历dp[i], 取其中的最值。

```cpp
int longestIncreasingSubsequence(vector<int>& nums) {
    int n = nums.size();
    //1. 定义状态： 以nums[i]结尾的子序列的最值，
    //2. 初始状态:  默认为 1
    vector<int> dp(n, 1);
   
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++){
            //3. 状态转移方程
            ...达到某个条件
            dp[i] = 最值(dp[i], dp[j] + 1);
        }
    }
    //4. 处理返回值
    int res = dp[0];
    for(int i = 1; i < n; i++) {
        res = 最值(res, dp[i]);
    }
    return res;
}
```

例题：
- [300. 最长递增子序列]
- [53. 最大子序和]
- [354. 俄罗斯套娃信封问题（通过排序转换成最长递增子序列]

#### 字符串中子序列：

经典题： 最长公共子序列（LCS）

一般是两个字符串, dp[i][j] 指的是 **表示以 s1[0, i]，s2[0, j] 中的公共子序列的最值**

**字符串数组模板**：

1、定义状态：dp[i][j] 表示以 s1[0, i]，s2[0, j] 中的公共子序列的最值

2、初始状态 

3、状态转移方程: 通过判断s1[i] 与 s2[j], 来决定更新d[i][j]

4、处理最终结果: 一般是dp[n][m]，因为dp没有没有明确是以什么结尾，而是表示范围内的最值

```cpp
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
                    dp[i][j] = dp[i - 1][j - 1] + ...
                } else {
                    dp[i][j] = 最值 dp[i - 1][j], dp[i][j - 1]
                }
            }
        }

        //4. 处理结果
        return dp[n][m];
    }
```
例题：
- [1143. 最长公共子序列]
- [516. 最长回文子序列]




https://mp.weixin.qq.com/s/ZhPEchewfc03xWv9VP3msg