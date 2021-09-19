## 673. 最长递增子序列的个数

### 题目

https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/

### 思路1： 动态规划

**技巧**

```C++
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1); //以i结尾的子序列，最大序列长度
        vector<int> count(n, 1); //以i结尾的子序列，最大序列的个数

        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    if(dp[j] + 1> dp[i]){
                        dp[i] = dp[j] + 1;
                        count[i] = count[j]; //更新为新的count值
                    } else if(dp[j] + 1 == dp[i]){
                        count[i] += count[j];
                    }
                }
            }
        }

        int length = 0;
        for(int i = 0; i < n; i++){
            length = max(length, dp[i]);
        }

        int res = 0;
        for(int i = 0; i < n; i++){
            if(dp[i] == length) res += count[i];
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n^2)
空间复杂度：O(n)


### 思路2： 贪心 +前缀和+二分查找