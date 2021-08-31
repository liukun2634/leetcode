### 847. 访问所有节点的最短路径

#### 题目
https://leetcode-cn.com/problems/shortest-path-visiting-all-nodes/

#### 思路1： BFS + 状态压缩

首先，考虑最短路径能够访问所有节点，使用BFS，一步一步扩展可以找到结果。

但是，由于中间存在很多重复探索过程，可以通过记录访问路径，然后排除。这里就可以使用状态压缩的技巧，由于题目n最多为12， 可以用一个int值来存档访问节点，并且用一个二维数组 visited 记录所有的访问情况。

https://leetcode-cn.com/problems/shortest-path-visiting-all-nodes/solution/gtalgorithm-tu-jie-fa-ba-hardbian-cheng-v5knb/

技巧：
- BFS 遍历 (queue)
- 状态压缩 (mask, 通过 1 << i 和 mask | (1 << next) 实现)

```cpp
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        //三个属性，idx，mask，dist
        queue<tuple<int, int, int>> q; 
        //记录表示以i为开始节点的，各个状态是否已经访问过
        vector<vector<bool>> visited(n, vector<bool>(1 << n));
        for(int i = 0; i < n; i++) {
            q.push({i, 1 << i, 0});
            visited[i][1 << i] = true;
        }

        while(!q.empty()) {
            auto [idx, mask, dist] = q.front();
            q.pop();
            
            //找到答案
            if(mask == (1 << n) - 1) return dist;

            for(int neibor : graph[idx]) {
                //计算下一状态 nextmask
                int nextmask = mask | (1 << neibor);
                if(!visited[neibor][nextmask]){
                   q.push({neibor, nextmask, dist + 1});
                   visited[neibor][nextmask] = true;
                }
            }
        }
        return 0;
    }
};
```

#### 思路2： Floyd + 状压 DP
