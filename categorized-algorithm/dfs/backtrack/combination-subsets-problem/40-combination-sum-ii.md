## 40. 组合总和 II

### 题目

https://leetcode-cn.com/problems/combination-sum-ii/

### 思路1： 回溯思路1 - 当前数字选择或者不选择

先排序，然后对于重复的数字，保证只有前面相同的数字存在于结果，才会将当前相同数字放入，否则就跳过当前数字。相比于39题，增加了一个visited数组表明前面的数字有没有被加入，只有为true的时候，当前数字可加入。

```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        int n = candidates.size();
        sort(candidates.begin(), candidates.end());
        vector<int> selected;
        vector<bool> visited(n);
        backtrack(0, candidates, selected, visited, target);
        return res;
    }

     void backtrack(int start, vector<int>& candidates, vector<int>& selected, vector<bool>& visited, int target){
        if(target == 0) {
            res.push_back(selected);
            return;
        }

        //因为排序了，所以如果当前数都大了，可以直接返回
        if(start == candidates.size() ||　candidates[start] > target) return;

        //不选择当前数
        backtrack(start + 1, candidates, selected, visited, target);

       //存在相同数所以跳过选择当前数
        if(start > 0 && candidates[start] == candidates[start - 1] && !visited[start - 1]) return;

         //选择当前数
        selected.push_back(candidates[start]);
        visited[start] = true;
        backtrack(start + 1, candidates, selected, visited, target - candidates[start]);
        selected.pop_back();
        visited[start] = false;
     }
};
```

**复杂度分析**

时间复杂度：O(n * 2^n) 最后结果赋值的 n * 每个数字选或者不选 - 剪枝复杂度
空间复杂度：

### 思路2： 回溯思路2 - 返回结果的当前位置放哪一个数

```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        int n = candidates.size();
        sort(candidates.begin(), candidates.end());
        vector<int> selected;
        vector<bool> visited(n);
        backtrack(0, candidates, selected, visited, target);
        return res;
    }

     void backtrack(int start, vector<int>& candidates, vector<int>& selected, vector<bool>& visited, int target){
        int n = candidates.size();
        for(int i = start; i < n; i++){
            //存在相同数所以跳过选择当前数
            if(i > 0 && candidates[i] == candidates[i - 1] && !visited[i - 1]) continue;
            if(candidates[i] < target) {
                selected.push_back(candidates[i]);
                visited[i] = true;
                backtrack(i + 1, candidates, selected, visited, target - candidates[i]);
                selected.pop_back();
                visited[i] = false;
            } else if(candidates[i] == target) {
                selected.push_back(candidates[i]);
                res.push_back(selected);
                selected.pop_back();
                return;
            } else{
                //当前值大于target，因为排序，后面的也没必要再看了
                return;
            }
        }
     }
};
```