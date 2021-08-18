### 77. 组合

#### 题目

https://leetcode-cn.com/problems/combinations/

#### 思路1：回溯算法

不需要额外的used[i]，或者状态压缩的state 记录是否访问过（这样会超时，时间复杂度 O(n * n!))

而是通过一个start，标识下一次开始遍历的位置。

```cpp
class Solution {
public:
    vector<vector<int>> res;
    int n, k;
    vector<vector<int>> combine(int _n, int _k) {
        n = _n;
        k = _k;
        vector<int> comb(k);
        backtrack(0, 1, comb);
        return res;
    }

    void backtrack(int pos, int start, vector<int>& comb){
        if(pos == k) {
            res.push_back(comb);
            return;
        }
       
        for(int i = start; i <= n; i++) {
            comb[pos] = i;
            backtrack(pos + 1, i + 1, comb);
        }
    }
};
```

**复杂度分析**

时间复杂度：O(n * 2^n) n是最后压入数组的时间
空间复杂度：O(n * 2^n) 存储结果的时间


### 思路2： 递归遍历获取所有子序列

每个数组选或者不选

