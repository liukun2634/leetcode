### 53. 最大子序和

#### 题目

https://leetcode-cn.com/problems/maximum-subarray/

#### 思路1： 动态规划

该题是求连续子数组和最大，首先可能会考虑滑动窗口，但是仔细思考一下，由于有负数的存在，并不能知道在什么时候收缩窗口。那么就不能使用滑动窗口。

好在子序列问题，不管是否有序，均考虑用动态规划来做。

1、定义状态：**dp[i] 是以nums[i]结尾的最大子序和**

2、状态转移方程：dp[i] = max(nums[i], dp[i-1] + nums[i]) 

3、初始状态：dp[0] = nums[0]

4、最终结果：res = max(res, dp[i]) (i = 0...n-1)

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        //1. 定义状态： 以nums[i]结尾的最大子序和，默认最小为INT_MIN
        vector<int> dp(n, INT_MIN); 
        //2. 初始状态
        dp[0] = nums[0];
        for(int i = 1; i < n; i++) {
            //3. 状态转移方程
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
        }
        //4.返回结果
        int res = dp[0];
        for(int i = 1; i < n; i++) {
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

**优化**
由于只dp[i]只与前面一个dp[i-1]相关，考虑用滚动数组优化空间复杂度：

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        //滚动数组优化
        int cur = nums[0];
        int res = nums[0];
        for(int i = 1; i < n; i++) {
            cur = max(nums[i], cur + nums[i]);
            res = max(res, cur);
        }
        return res;
    }
};
```
**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)


#### 思路2： 分治法

https://leetcode-cn.com/problems/maximum-subarray/solution/zui-da-zi-xu-he-by-leetcode-solution/