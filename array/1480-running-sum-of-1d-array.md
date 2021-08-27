## 1480. 一维数组的动态和

### 题目

https://leetcode-cn.com/problems/running-sum-of-1d-array/

### 思路： 原地修改

前缀和裸题

```C++
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();
        for(int i = 1; i < n; i++){
            nums[i] += nums[i-1];
        }
        return nums;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(1)