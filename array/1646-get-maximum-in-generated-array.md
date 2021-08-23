## 1646. 获取生成数组中的最大值

### 题目

https://leetcode-cn.com/problems/get-maximum-in-generated-array/

### 思路： 模拟

注意： 最大情况并不是最后两个的一个，还是要遍历所有的数字。

```C++
class Solution {
public:
    int getMaximumGenerated(int n) {
        if(n == 0) return 0;
        vector<int> nums(n + 1);
        nums[0] = 0;
        nums[1] = 1;
        int res = 1;
        for(int i = 2; i < n + 1; i++){
            nums[i] = i % 2 == 0 ? nums[i/2] : nums[i/2] + nums[i/2 + 1];
            res = max(res, nums[i]); 
        }
        return res;
    }
};
```

**复杂度分析**

时间复杂度：O(n)
空间复杂度：O(n)