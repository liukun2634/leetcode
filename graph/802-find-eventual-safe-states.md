### 802. 找到最终的安全状态

#### 题目

https://leetcode-cn.com/problems/find-eventual-safe-states/

#### 思路 1： DFS + 清空邻居节点

考虑对所有点进行DFS遍历判断是否有环，如果到达已经访问过的节点，就认为存在环。时间复杂度将是O(N^2)，会超时。(DFS模板关键，先设visited为true，然后遍历完，设回为false)

这里还有一个技巧就是在DFS结束后将所有相邻节点情况，从而可以将复杂度缩小到O(N)。其实原理就是认为该节点已经是安全节点，后序到达该节点，可以直接返回true了。

技巧：
- DFS 图遍历
- **将节点的所有相邻节点清空从而标记为安全节点**

```cpp
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
        int n = graph.size();
        vector<int> visited(n, false);
        function<bool(int)> dfs;
        dfs = [&](int i) -> bool {
            if (visited[i]) return false;
            visited[i] = true;
            for (auto neibor : graph[i]) {
                if (!dfs(neibor))  return false;
            }
            visited[i] = false;
            graph[i].clear(); 
            return true;
        };
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (dfs(i))
                ans.push_back(i);
        }
        return ans;
    }
};
```

v 为顶点数，e 为边数:

- 时间复杂度：O(v + e)
- 空间复杂度：O(v) 



#### 思路 2： DFS + 三色标记

https://leetcode-cn.com/problems/find-eventual-safe-states/solution/zhao-dao-zui-zhong-de-an-quan-zhuang-tai-yzfz/

思路2与思路1其实是一样的，标记为黑色的安全节点与将节点邻接表清空的作用是相同的。

```cpp
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        int n = graph.size();
        vector<int> color(n);

        function<bool(int)> safe = [&](int x) {
            if (color[x] > 0) {
                return color[x] == 2;
            }
            color[x] = 1;
            for (int y : graph[x]) {
                if (!safe(y)) {
                    return false;
                }
            }
            color[x] = 2;
            return true;
        };

        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (safe(i)) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

#### 思路 3： 拓扑排序

To Learning...