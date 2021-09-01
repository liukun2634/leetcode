## 797. 所有可能的路径

### 题目

https://leetcode-cn.com/problems/all-paths-from-source-to-target/

### 思路1：DFS - 图的遍历 

因为是有向无环图，不需要额外的visited数组。

图的遍历相比于回溯算法，就是会把根节点计入统计，如果存在visited，那么也会把visited 放在for 的外面。 可以与思路2 形式对比。

graph 这里就是邻接表，最方便遍历了。

```C++
class Solution {
public:
    vector<vector<int>> res;
    int n;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        n = graph.size();
        vector<int> path;
        traverse(graph, 0, path);
        return res;
    }

    void traverse(vector<vector<int>>& graph, int s, vector<int>& path){
        //path 可以理解成visited, 放在外面因为根节点也要计入结果
        path.push_back(s);
        if(s == n - 1) {
            res.push_back(path);
        }
        for(int next : graph[s]){
            traverse(graph, next, path);
        }
        path.pop_back();
    }
};
```

**复杂度分析**

时间复杂度：O(n * 2^n) 2^n为路径数
空间复杂度：O(n)

### 思路2：DFS - 回溯算法

回溯算法就是判断每个子节点加入和不加入的选择。因而需要额外先将根节点压入。

 ```C++
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> path;
        //压入根节点
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

时间复杂度：O(n * 2^n) 2^n为路径数
空间复杂度：O(n)