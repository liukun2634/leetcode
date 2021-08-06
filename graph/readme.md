# 图总结

## 技巧总结

- DFS图遍历
- BFS图遍历
- 拓扑排序 （判断是否有环）
- 状态压缩


### BFS 图遍历
https://leetcode-cn.com/problems/shortest-path-visiting-all-nodes/solution/gtalgorithm-tu-jie-fa-ba-hardbian-cheng-v5knb/

```cpp
// 1.初始化队列及标记数组，存入起点
queue<pair<int, int>> q;
vector<bool> vis(n);

q.push({begin_node, 0}); // 存入起点，起始距离0，标记
vis[begin_node] = true;

// 2.开始搜索
while(!q.empty()) {
    auto [cur, dist] = q.front(); // 弹出队头元素
    q.pop();

    // 找到答案，返回结果
    if(cur == target) return dist;
    
    action(cur); //有些题目需要对当前元素做处理

    for(int x : cur.children) {
        if(!vis[x]) {
            q.push({x, dist + 1});
            vis[x] = true;
        }
    }
}
```