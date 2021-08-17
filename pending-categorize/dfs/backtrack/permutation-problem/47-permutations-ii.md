### 47. 全排列 II

#### 题目

https://leetcode-cn.com/problems/permutations-ii/

#### 思路1： 回溯 + set 剪枝

相比 46 全排列， 这里增加了可重复数字，但是结果需要唯一的排列。 因为去重首先考虑使用 set， 存储string 来剪枝，避免同样的前缀出现

```cpp
class Solution {
public:
    vector<vector<int>> res;
    set<string> existed;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int n = nums.size();
        vector<bool> used(n);
        vector<int> permute(n);
        backtrack(0, nums, used, permute, "");
        return res;
    }

    void backtrack(int pos, vector<int>& nums, vector<bool>& used, vector<int>& permute, string permuteString){
        int n = nums.size();
        if(existed.count(permuteString) != 0) return;
        if(permuteString != "") existed.insert(permuteString); 
        if(n == pos) {
            res.push_back(permute);
            return;
        }

        for(int i = 0; i < n; i++) {
            if(used[i] == false) {
                used[i] = true;
                permute[pos] = nums[i];
                backtrack(pos + 1, nums, used, permute, permuteString + to_string(nums[i]));
                //这里只需要used 还原
                used[i] = false;
            }
        }
    }
};
```

**复杂度分析**

时间复杂度：O(n! * n)
空间复杂度：O(n! * n)


#### 思路2： 回溯 + 排序预处理

**由于重复数组，可以先考虑排序，这样相邻的都是重复数字了。**

如果相邻的话 且 num[i]==nums[i-1] && !used[i-1]，就认为在这个位置num[i-1]已经使用过了，所以num[i]就直接跳过

这里其实还有一点绕，如果前面一个值没有这里判断显示没有使用，!used[i-1]， 其实是表明在上一个循环已经遍历过了。所以不需要再遍历了。


```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int n = nums.size();
        vector<bool> used(n);
        vector<int> permute(n);
        //预处理
        sort(nums.begin(), nums.end());
        backtrack(0, nums, used, permute);
        return res;
    }

    void backtrack(int pos, vector<int>& nums, vector<bool>& used, vector<int>& permute){
        int n = nums.size();
        if(n == pos) {
            res.push_back(permute);
            return;
        }

        for(int i = 0; i < n; i++) {
            //当前面一个同样的数已经加入过了，跳过当前值
            if(used[i] || i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            used[i] = true;
            permute[pos] = nums[i];
            backtrack(pos + 1, nums, used, permute);
            used[i] = false;
        }
    }
};
```