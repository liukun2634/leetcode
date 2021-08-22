## 39. 组合总和

### 题目

https://leetcode-cn.com/problems/combination-sum/



### 思路1： 回溯思路1 - 每个数字选择放或者不放
该题其实就是背包问题，每个数字可以选择放或者不放，但因为需要记录中间过程，采用回溯方法来写更为合适。

**要点：** 因为是求和，可以先对数组进行升序排序，便于剪枝。

```cpp
class Solution {
public:

    vector<vector<int>> res;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> selected;
        backtrack(0, candidates, selected, target);
        return res;
    }

    void backtrack(int start, vector<int>& candidates, vector<int>& selected, int target){
        if(target == 0) {
            res.push_back(selected);
            return;
        }

        int n = candidates.size();
        if(start == n) return;
        
        //选择当前数
        if(candidates[start] <= target) {
            selected.push_back(candidates[start]);
            backtrack(start, candidates, selected, target - candidates[start]);
            selected.pop_back();
        }  else{
            //剪枝：因为排序了，所以如果当前数都大了，可以直接返回
            return;
        }

        //不选择当前数
        backtrack(start + 1, candidates, selected, target);
        
    }
};

```

**复杂度分析**

时间复杂度：O (2 ^ n) 每次个数字被选择或者不选 - 剪枝
空间复杂度：

### 思路2： 回溯思路2 - 返回结果的每个位置的数字

结果的每个位置，都可以选择一个数加入，所以每一位都遍历从start 到 n。

剪枝条件：当前start 放不进去了

```cpp
class Solution {
public:

    vector<vector<int>> res;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> selected;
        backtrack(0, candidates, selected, target);
        return res;
    }

    void backtrack(int start, vector<int>& candidates, vector<int>& selected, int target){
        int n = candidates.size();
        for(int i = start; i < n; i++){
            if(candidates[i] < target) {
                selected.push_back(candidates[i]);
                backtrack(i, candidates, selected, target - candidates[i]);
                selected.pop_back();
            } else if(candidates[i] == target) {
                selected.push_back(candidates[i]);
                res.push_back(selected);
                selected.pop_back();
                return;
            } else{
                return;
            }
        }
        
    }
};
```

**复杂度分析**

时间复杂度：O (m ^ n) 返回结果的长度 n ^ m - 剪枝
空间复杂度：