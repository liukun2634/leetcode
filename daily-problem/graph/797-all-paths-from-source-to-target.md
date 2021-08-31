## 797. 所有可能的路径

### 题目

https://leetcode-cn.com/problems/all-paths-from-source-to-target/

### 思路：回溯算法

首先题目要求求得所有的路径，是标准的回溯例题。

因为题目是有向无环图，那么不回回到以前的节点，所以不需要额外的visited。

```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> path;
        path.push_back(0);
        backtrack(0, graph, path);
        return res;
    }

    void backtrack(int cur, vector<vector<int>>& graph, vector<int>& path){
        int n = graph.size();
        if(cur == n - 1) {
            res.push_back(path);
        }
        for(int next : graph[cur]){
                path.push_back(next);
                backtrack(next, graph, path);
                path.pop_back();
        }
    }
};
```

**复杂度分析**

时间复杂度：O(n * 2^n)  每个节点有选或者不选两种，然后 最坏结果要赋值n次
空间复杂度：O(n * 2^n) 总共2^n方案，最多n个元素