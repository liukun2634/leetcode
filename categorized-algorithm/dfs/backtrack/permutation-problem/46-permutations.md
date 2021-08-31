### 46. 全排列

#### 题目

https://leetcode-cn.com/problems/permutations/

#### 思路1：回溯模板 

最为经典全排列，套用回溯模板。

```cpp
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<bool> visited(n, false);
        vector<int> permute(n);
        dfs(0, nums, visited, permute);
        return res;
    }

    void dfs(int pos, vector<int>& nums, vector<bool>& visited, vector<int> permute){
        int n = nums.size();
        //终止条件
        if(pos == n) {
            res.push_back(permute);
            return;
        }

        for(int i = 0; i < n; i++){
            if(visited[i] == false) {
                visited[i] = true;
                permute[pos] = nums[i];
                dfs(pos + 1, nums, visited, permute);
                visited[i] = false;
            }
        }
    }
};
```

**复杂度分析**

时间复杂度：O(n! * n) 最后赋值答案时间为n
空间复杂度：O(n! * n) 结果保存

#### 思路2： 利用 next permutation的算法

https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-by-leetcode-solution/

第一遍从后向前扫描找寻第一个i 使得 a[i] < a[i + 1]

第二遍从后向前扫描找寻第一个 j 使得 a[i] < a[j]

交换 a[i] 和 a[j] 的值，reverse [i+ 1, n)



C++ 还提供 next_permutation() 库函数