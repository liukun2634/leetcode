## 90. 子集 II

### 题目

https://leetcode-cn.com/problems/subsets-ii/

### 思路1：回溯算法

对于 78 题 子集，  增加了排序， 在放去数据之前，增加对相邻元素判断，如果是在同位置的，那么就选择不放入。

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        //有重复，先排序
        sort(nums.begin(), nums.end());
        vector<int> subset;
        backtrack(0, nums, subset);
        return res;
    }

    void backtrack(int start, vector<int>& nums, vector<int>& subset){
        int n = nums.size();
        res.push_back(subset);
        if(start == n) return;

        for(int i = start; i < nums.size(); i++) {
            //判断是否能够加入nums[i]
            if(i == start || nums[i] != nums[i-1]){
                subset.push_back(nums[i]);
                backtrack(i + 1, nums, subset);
                subset.pop_back();
            }
        }
    }
};
```

**复杂度分析**

时间复杂度：O(n * 2^n) n是最后压入数组的时间
空间复杂度：O(n * 2^n) 存储结果的时间