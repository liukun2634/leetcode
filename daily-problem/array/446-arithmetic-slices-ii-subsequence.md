### 446. 等差数列划分 II - 子序列

#### 题目

https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/

#### 思路：动态规划

基于[413. 等差数列划分](https://leetcode-cn.com/problems/arithmetic-slices/), 将连续子等差数列改为可以不连续的弱等差数列。

由于没有连续，但依然还是求子序列，依然考虑动态规划的方案。

定义状态： dp[i][d] 表示尾项为 nums[i]，公差为 d 的弱等差子序列的个数。

状态转移方程： dp[i][d] = dp[j][d] + 1 (j < i) 

其中，j 可以视为等差数列的倒数第二项。因为等差数列至少要为 3 项，那么对于上面的公式，dp[i][d]在两项时候就被加为1，所以最后结果可以计算dp[j][d] 的总和即可。

根据题目的取值范围，因为差值d可能很大，第二维如果用数组可能下标不够，所以使用哈希表来存储差值。

```cpp
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if(nums.size() < 3) return 0;

        int n = nums.size();
        vector<unordered_map<long, int>> dp(n, unordered_map<long, int>());
        int res = 0;
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < i; j++) {
                //1.差值d可能超过int，用long存
                long d = (long)nums[i] - nums[j];
                //2.同一个i可能存在相同的d, 这里要用+=
                dp[i][d] += dp[j][d] + 1;
                //3.加的是-1的结果，因为最开始两个[i][j]初始化值为1
                res += dp[j][d]; 
            }
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n^2)