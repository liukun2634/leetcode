## 78. 子集

### 题目

https://leetcode-cn.com/problems/subsets/

### 思路1： 回溯算法

参考 组合，只不过这里的记录数组还需要pop_back()

因为使用used 时间复杂度会超时 O(n * n!)，这里利用最后数据不会相同的性质，通过一个start，标识下一次开始遍历的位置。

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<int> subset;
        backtrack(0, nums, subset);
        return res;
    }

    void backtrack(int start, vector<int>& nums, vector<int>& subset){
        int n = nums.size();
        if(start > n) return;
        res.push_back(subset);
        for(int i = start; i < n; i++){
            subset.push_back(nums[i]);
            //下一次开始是i + 1
            backtrack(i + 1, nums, subset);
            subset.pop_back();
        } 

    } 
};
```

**复杂度分析**

时间复杂度：O(n * 2^n) n是最后压入数组的时间
空间复杂度：O(n * 2^n) 存储结果的时间



### 思路2： 递归遍历获取所有子序列

前面是利用了不等的性质，下一个起始左边肯定在i + 1。

还有一种思路同样使用递归，即对数组中的每个数字选或者不选，分别进行深度优先遍历，递归得到所有子序列。 


```cpp

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<int> subset;
        dfs(0, nums, subset);
        return res;
    }

    void dfs(int start, vector<int>& nums, vector<int>& subset){
        int n = nums.size();
        if(start == n) {
            //这里是递归到头了才加入res
            res.push_back(subset);
            return;
        }
     

        subset.push_back(nums[start]);
        dfs(start + 1, nums, subset);
        subset.pop_back();
        dfs(start + 1, nums, subset);
    } 
};

```


### 思路3： 迭代 + 状态压缩

正常使用used数组标记会超时，使用state 标记使用的数据，然后遍历所有状态

https://leetcode-cn.com/problems/subsets/solution/zi-ji-by-leetcode-solution/

**复杂度分析**

时间复杂度：O(n * 2^n) 比全排列 少n，

